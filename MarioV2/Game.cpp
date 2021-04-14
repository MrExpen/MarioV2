#include <iostream>
#include <fstream>
#include <algorithm>
#include "Game.h"
#include "Mushroom.h"

void Game::Update(float time)
{
	Player.UpdateX(time);
	for (auto wall : Walls)
	{
		if (Player.isIntersect(*wall))
		{
			if (Player.Speed.x > 0)
			{
				Player.Position.x = wall->Position.x - Player.Size.x;
			}
			else if (Player.Speed.x < 0)
			{
				Player.Position.x = wall->Position.x + wall->Size.x;
			}
			else
			{
				throw exception();
			}
			Player.Speed.x = 0;
		}
	}

	for (auto enemy : Enemies)
	{
		enemy->UpdateX(time);
		for (auto wall : Walls)
		{
			if (enemy->isIntersect(*wall))
			{
				if (enemy->Speed.x > 0)
				{
					enemy->Position.x = wall->Position.x - enemy->Size.x;
				}
				else if (enemy->Speed.x < 0)
				{
					enemy->Position.x = wall->Position.x + wall->Size.x;
				}
				else
				{
					throw exception();
				}
				enemy->Speed.x *= -1;
			}
		}
	}

	for (int i = 0; i < Enemies.size(); i++)
	{
		for (int j = i + 1; j < Enemies.size(); j++)
		{
			if (Enemies[i]->isIntersect(*Enemies[j]))
			{
				Enemies[i]->Speed.x *= -1;
				Enemies[j]->Speed.x *= -1;
			}
		}
	}

	Player.UpdateY(time);
	for (auto wall : Walls)
	{
		if (Player.isIntersect(*wall))
		{
			if (Player.Speed.y > 0)
			{
				Player.Position.y = wall->Position.y + wall->Size.y;
				Player.Speed.y = -0.00001;
			}
			else if (Player.Speed.y < 0)
			{
				Player.Position.y = wall->Position.y - Player.Size.y;
				Player.Speed.y = 0;
			}
			else
			{
				throw exception();
			}
		}
	}

	for (auto enemy : Enemies)
	{
		enemy->UpdateY(time);
		for (auto wall : Walls)
		{
			if (enemy->isIntersect(*wall))
			{
				if (enemy->Speed.y > 0)
				{
					enemy->Position.y = wall->Position.y + wall->Size.y;
				}
				else if (enemy->Speed.y < 0)
				{
					enemy->Position.y = wall->Position.y - enemy->Size.y;
				}
				else
				{
					throw exception();
				}
				enemy->Speed.y = 0;
			}
		}
	}

	for (auto enemy : Enemies)
	{
		if (enemy->isIntersect(Player))
		{
			switch (enemy->onPlayerEnter(Player))
			{
			case GameAction::PlayerTakeDamage:
				Player.Position = Player.SpawnPoint;

				break;
			case GameAction::PlayerDie:
				LoadLevel(LevelName);
				break;
			case GameAction::EnemyTakeDamage:
				//TODO
				break;
			case GameAction::EnemyDie:
				Enemies.erase(find(Enemies.begin(), Enemies.end(), enemy));
				enemy->~BaseEnemy();
				break;
			}
		}
	}
}

void Game::Draw(RenderWindow& window)
{
	for (auto wall : Walls)
	{
		wall->Draw(window);
	}
	for (auto enemy : Enemies)
	{
		enemy->Draw(window);
	}
	this->Player.Draw(window);
}

void Game::LoadLevel(string levelName)
{
	LevelName = levelName;
	for (auto wall : Walls)
	{
		wall->~Wall();
	}
	Walls.clear();
	for (auto enemy : Enemies)
	{
		enemy->~BaseEnemy();
	}
	Enemies.clear();

	ifstream fin(levelName);
	int n = 0;
	for (string line; getline(fin, line); )
	{
		for (int i = 0; i < line.size(); i++)
		{
			switch (line[i])
			{
			case '#':
				Walls.push_back(new Wall(Vector2f(32 * i, 32 * n)));
				break;
			case '@':
				Player = Player::Player(Vector2f(32 * i, 32 * n));
				break;
			case '!':
				Enemies.push_back(new Mushroom(Vector2f(32 * i, 32 * n)));
				break;
			}
		}
		n++;
	}
	fin.close();
	State = GameState::GameOn;
}

Game::Game()
{
	State = GameState::GamePaused;
}
