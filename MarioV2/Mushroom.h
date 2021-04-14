#pragma once
#include "BaseEnemy.h"

#define DEFAULTSPEEDX 0.5

class Mushroom :
    public BaseEnemy
{
public:
	Mushroom(Vector2f position);
	virtual GameAction onPlayerEnter(Player& player) override;
	virtual Drawable* GetSprite() override;
	~Mushroom();
};

