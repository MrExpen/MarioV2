#include <iostream>
#include <fstream>
#include "Game.h"

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
