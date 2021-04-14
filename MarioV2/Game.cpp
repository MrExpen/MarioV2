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
				Player.Position.x = wall->Position.x + Player.Size.x;
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
				Player.Position.x = wall->Position.x + Player.Size.x;
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

Game::Game()
{
	State = GameState::GamePaused;
}
