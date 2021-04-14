#include "Game.h"

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
