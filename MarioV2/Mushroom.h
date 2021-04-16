#pragma once
#include "BaseEnemy.h"
#include "Direction.h"

#define DEFAULTSPEEDX 0.5
#define WAY_TO_ACHIVE_MUSHROOM 20
#define MUSHROOM_DEAD_TIME 2

class Mushroom :
    public BaseEnemy
{
public:
	Mushroom(Vector2f position);
	float Way;
	Direction Direction;
	Clock Timer;
	virtual void UpdateX(float time) override;
	virtual int GetTextureIndex() override;
	virtual GameAction onPlayerEnter(Player& player) override;
	virtual Drawable* GetSprite() override;
	~Mushroom();
};

