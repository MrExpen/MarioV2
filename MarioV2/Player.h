#pragma once
#include "BaseEntity.h"
#include "Direction.h"
#include "Move.h"

#define MAX_PLAYER_HP 3
#define MAX_PLAYER_SPEED_X 3
#define MAX_PLAYER_SPEED_Y 100
#define MIN_PLAYER_SPEED_X -MAX_PLAYER_SPEED_X
#define MIN_PLAYER_SPEED_Y -MAX_PLAYER_SPEED_Y
#define JUMP_SPEED 10
#define ACCELERATION_X 0.1
#define ACCELERATION_Y 0.3
#define SPEED_X_ACCELERATION 0.5

class Player :
    public BaseEntity
{
public:
    short HealthPoints;
    Vector2f SpawnPoint;
    Direction Direction;
    Move Move;
    void Jump();
    virtual void UpdateX(float time) override;
    virtual void UpdateY(float time) override;
    bool isIntersect(BaseEntity& entity);
    Player(Vector2f position);
    Player();
};
