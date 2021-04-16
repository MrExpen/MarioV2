#pragma once
#include "BaseEntity.h"
#include "Direction.h"
#include "Move.h"
#include "GameAction.h"

#define MAX_PLAYER_HP 3
#define MAX_PLAYER_SPEED_X 1.5
#define MIN_PLAYER_SPEED_X -MAX_PLAYER_SPEED_X
#define JUMP_SPEED 5.3
#define ACCELERATION_X 0.1
#define SPEED_X_ACCELERATION 0.5
#define JUMP_KILL_SPEED 2
#define WAY_TO_ACHIVE 30
#define PLAYER_DEAD_FLY_TIME 2

class Player :
    public BaseEntity
{
public:
    short HealthPoints;
    Vector2f SpawnPoint;
    Direction Direction;
    Move Move;
    Clock Timer;
    float Way;
    void Jump();
    virtual void UpdateX(float time) override;
    virtual Drawable* GetSprite() override;
    virtual int GetTextureIndex() override;
    GameAction TakeDamage();
    Player(Vector2f position);
    Player();
};
