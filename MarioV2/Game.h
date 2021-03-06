#pragma once
#include <vector>
#include "Wall.h"
#include "Player.h"
#include "BaseEnemy.h"
#include "GameState.h"
#include "Mushroom.h"
#include <SFML/Graphics.hpp>
#include <string>

#define W 800
#define H 600

using namespace std;
using namespace sf;

class Game
{
public:
	vector<Wall*> Walls;
	vector<Mushroom*> Mushrooms;
	Player Player;
	string LevelName;
	GameState State;
	Vector2f CameraCenter;
	Vector2f CameraSize;
	void Update(float time);
	void Draw(RenderWindow& window);
	void LoadLevel(string levelName);
	View View;
	Game();

private:
	vector<Texture*>* WallsTextures;
	vector<Texture*>* PlayerTextures;
	vector<Texture*>* MushroomTextures;
};
