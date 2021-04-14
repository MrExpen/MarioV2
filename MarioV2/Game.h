#pragma once
#include <vector>
#include "Wall.h"
#include "Player.h"
#include "BaseEnemy.h"
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include <string>

using namespace std;
using namespace sf;

class Game
{
public:
	vector<Wall*> Walls;
	vector<BaseEnemy*> Enemies;
	Player Player;
	string LevelName;
	GameState State;
	Vector2f CameraCenter;
	Vector2f CameraSize;
	void Update(float time);
	void Draw(RenderWindow& window);
	void LoadLevel(string levelName);
	Game();
};
