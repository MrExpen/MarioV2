#pragma once
#include "BaseEnemy.h"
#include "Direction.h"

#define DEFAULTSPEEDX 0.5
#define WAY_TO_ACHIVE_MUSHROOM 20
#define MUSHROOM_DEAD_TIME 200

class Mushroom :
    public BaseEnemy
{
public:
	Mushroom(Vector2f position, vector<Texture*>* Textures);
	float Way;
	Direction Direction;
	float Timer;
	virtual void UpdateX(float time) override;
	virtual int GetTextureIndex() override;
	virtual GameAction onPlayerEnter(Player& player) override;
	virtual void BuildSprite(Sprite& sprite) override;
};

