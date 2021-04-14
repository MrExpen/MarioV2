#pragma once
#include "BaseEntity.h"
#include "GameAction.h"
#include "Player.h"

class BaseEnemy :
    public BaseEntity
{
public:
    BaseEnemy(Vector2f position, Vector2f speed, bool iskinematic, Vector2f size);
    BaseEnemy(Vector2f position, Vector2f speed);
    BaseEnemy(Vector2f position);
    virtual GameAction onPlayerEnter(Player& player);
    virtual void Die();
    ~BaseEnemy();
};
