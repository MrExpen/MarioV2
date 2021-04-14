#pragma once
#include "BaseEntity.h"
#include "Direction.h"

#define MAX_PLAYER_HP 3
#define MAX_PLAYER_SPEED_X 1
#define MAX_PLAYER_SPEED_Y 1
#define MIN_PLAYER_SPEED_X -MAX_PLAYER_SPEED_X
#define MIN_PLAYER_SPEED_Y -1
#define JUMP_SPEED 1;

class Player :
    public BaseEntity
{
public:
    short HealthPoints;
    Vector2f SpawnPoint;
    Direction Direction;
    void Jump();
    virtual void UpdateX(float time) override;
    virtual void UpdateY(float time) override;
    Player(Vector2f position);
    Player();
};
