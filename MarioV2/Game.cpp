#include <iostream>
#include <fstream>
#include <algorithm>
#include "Game.h"
#include "Mushroom.h"

void Game::Update(float time)
{
	Player.UpdateX(time);

	if (Player.Position == Player.SpawnPoint)
	{
		this->View.setCenter(Player.Position);
	}

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

	for (auto mushroom : Mushrooms)
	{
		if (!mushroom->isAlive)
		{
			Mushrooms.erase(find(Mushrooms.begin(), Mushrooms.end(), mushroom));
			delete mushroom;
			continue;
		}
		mushroom->UpdateX(time);
		for (auto wall : Walls)
		{
			if (mushroom->isIntersect(*wall))
			{
				if (mushroom->Speed.x > 0)
				{
					mushroom->Position.x = wall->Position.x - mushroom->Size.x;
				}
				else if (mushroom->Speed.x < 0)
				{
					mushroom->Position.x = wall->Position.x + wall->Size.x;
				}
				else
				{
					throw exception();
				}
				mushroom->Speed.x *= -1;
			}
		}
	}

	for (int i = 0; i < Mushrooms.size(); i++)
	{
		for (int j = i + 1; j < Mushrooms.size(); j++)
		{
			if (Mushrooms[i]->isIntersect(*Mushrooms[j]))
			{
				Mushrooms[i]->Speed.x *= -1;
				Mushrooms[j]->Speed.x *= -1;
			}
		}
	}

	Player.UpdateY(time);
	auto a = Walls.end();
	a--;
	Wall lastwall = *(*a);
	if (Player.Position.y - lastwall.Position.y > 64 && Player.canCollide)
	{
		Player.Speed = Vector2f(0, PLAYER_DEAD_JUMP_SPEED);
		Player.canCollide = false;
		Player.Timer = 0;
	}

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

	for (auto mushroom : Mushrooms)
	{
		mushroom->UpdateY(time);
		for (auto wall : Walls)
		{
			if (mushroom->isIntersect(*wall))
			{
				if (mushroom->Speed.y > 0)
				{
					mushroom->Position.y = wall->Position.y + wall->Size.y;
				}
				else if (mushroom->Speed.y < 0)
				{
					mushroom->Position.y = wall->Position.y - mushroom->Size.y;
				}
				else
				{
					throw exception();
				}
				mushroom->Speed.y = 0;
			}
		}
	}

	for (auto mushroom : Mushrooms)
	{
		if (mushroom->isIntersect(Player))
		{
			switch (mushroom->onPlayerEnter(Player))
			{
			case GameAction::PlayerTakeDamage:
				Player.Speed = Vector2f(0, PLAYER_DEAD_JUMP_SPEED);
				Player.canCollide = false;
				Player.Timer = 0;
				break;
			case GameAction::PlayerDie:
				LoadLevel(LevelName);
				break;
			case GameAction::EnemyTakeDamage:
				//TODO
				break;
			case GameAction::EnemyDie:
				mushroom->canCollide = false;
				mushroom->isKinematic = false;
				mushroom->Timer = 0;
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
	for (auto enemy : Mushrooms)
	{
		enemy->Draw(window);
	}
	this->Player.Draw(window);
	if (Player.Direction == Direction::Right && (Player.Position.x - this->View.getCenter().x > 32 || this->View.getCenter().x - Player.Position.x < -128))
	{
		this->View.move(Vector2f((Player.Position.x - this->View.getCenter().x) / 32.0f, 0));
	}
	else if (Player.Direction == Direction::Left && (this->View.getCenter().x - Player.Position.x > 32 || Player.Position.x - this->View.getCenter().x < -128))
	{
		this->View.move(Vector2f((Player.Position.x - this->View.getCenter().x) / 32.0f, 0));
	}
	if (Player.Speed.y == 0 && abs(Player.Position.y - this->View.getCenter().y) > 32)
	{
		this->View.move(Vector2f(0, (Player.Position.y - this->View.getCenter().y) / 16.0f));
	}
	else if (abs(Player.Position.y - this->View.getCenter().y) > 256 && Player.canCollide)
	{
		this->View.move(Vector2f(0, (Player.Position.y - this->View.getCenter().y) / 16.0f));
	}
	window.setView(this->View);
}

void Game::LoadLevel(string levelName)
{
	LevelName = levelName;
	for (auto wall : Walls)
	{
		delete wall;
	}
	Walls.clear();
	for (auto mushroom : Mushrooms)
	{
		delete mushroom;
	}
	Mushrooms.clear();

	ifstream fin(levelName);
	int n = 0;
	for (string line; getline(fin, line); )
	{
		for (int i = 0; i < line.size(); i++)
		{
			switch (line[i])
			{
			case '#':
				Walls.push_back(new Wall(Vector2f(32 * i, 32 * n), 0, WallsTextures));
				break;
			case '@':
				Player = Player::Player(Vector2f(32 * i, 32 * n), PlayerTextures);
				this->View.setCenter(Player.Position);
				this->View.setSize(W, H);
				break;
			case '!':
				Mushrooms.push_back(new Mushroom(Vector2f(32 * i, 32 * n), MushroomTextures));
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

	WallsTextures = new vector<Texture*>();
	MushroomTextures = new vector<Texture*>();
	PlayerTextures = new vector<Texture*>();

	for (int i = 0; i < 3; i++)
	{
		Texture* texture = new Texture();
		texture->loadFromFile("Images\\Mushroom.png", IntRect(i * 32, 0, 32, 32));
		MushroomTextures->push_back(texture);
	}

	for (int i = 0; i < 7; i++)
	{
		Texture* texture = new Texture();
		texture->loadFromFile("Images\\Walls.png", IntRect(i * 32, 0, 32, 32));
		WallsTextures->push_back(texture);
	}

	for (int i = 0; i < 5; i++)
	{
		Texture* texture = new Texture();
		texture->loadFromFile("Images\\Mario.png", IntRect(i * 32, 0, 32, 32));
		PlayerTextures->push_back(texture);
	}
}
