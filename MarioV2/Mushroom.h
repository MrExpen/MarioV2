#pragma once
#include "BaseEnemy.h"

#define DEFAULTSPEEDX 0.5
#define ACCELERATION_Y 0.1
#define MAX_MUSHROOM_SPEED_Y 100
#define MIN_PLAYER_SPEED_Y -MAX_MUSHROOM_SPEED_Y

class Mushroom :
    public BaseEnemy
{
public:
	Mushroom(Vector2f position);
	virtual GameAction onPlayerEnter(Player& player) override;
	virtual Drawable* GetSprite() override;
	~Mushroom();
};

