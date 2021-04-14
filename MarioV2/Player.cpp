#include "Player.h"

void Player::Jump()
{
	if (Speed.y == 0)
	{
		Speed.y = JUMP_SPEED;
	}
}

void Player::UpdateX(float time)
{
	if (Move == Move::Right)
	{
		Speed.x += SPEED_X_ACCELERATION * time;
		Move = Move::None;
	}
	else if (Move == Move::Left)
	{
		Speed.x -= SPEED_X_ACCELERATION * time;
		Move = Move::None;
	}
	else if (Move == Move::None)
	{
		if (Speed.x > 0)
		{
			Speed.x -= ACCELERATION_X * time;
			if (Speed.x < 0)
			{
				Speed.x = 0;
			}
		}
		else if (Speed.x < 0)
		{
			Speed.x += ACCELERATION_X * time;
			if (Speed.x > 0)
			{
				Speed.x = 0;
			}
		}
	}

	if (Speed.x > MAX_PLAYER_SPEED_X)
	{
		Speed.x = MAX_PLAYER_SPEED_X;
	}
	else if (Speed.x < MIN_PLAYER_SPEED_X)
	{
		Speed.x = MIN_PLAYER_SPEED_X;
	}

	BaseEntity::UpdateX(time);
	if (Speed.x > 0)
		this->Direction = Direction::Right;
	else if (Speed.x < 0)
		this->Direction = Direction::Left;
}

void Player::UpdateY(float time)
{
	Speed.y -= ACCELERATION_Y * time;
	BaseEntity::UpdateY(time);
	if (Speed.y > MAX_PLAYER_SPEED_Y)
	{
		Speed.y = MAX_PLAYER_SPEED_Y;
	}
	else if (Speed.y < MIN_PLAYER_SPEED_Y)
	{
		Speed.y = MIN_PLAYER_SPEED_Y;
	}
}

GameAction Player::TakeDamage()
{
	if (--HealthPoints <= 0)
	{
		return GameAction::PlayerDie;
	}
	return GameAction::PlayerTakeDamage;
}
//TODO: 32x32
Player::Player(Vector2f position) : BaseEntity(true, true, Vector2f(32, 32), position, Vector2f(0, 0))
{
	this->Direction = Direction::Right;
	this->HealthPoints = MAX_PLAYER_HP;
	this->SpawnPoint = position;
	this->Move = Move::None;
}
//TODO: 32x32
Player::Player() : BaseEntity(true, true, Vector2f(32, 32), Vector2f(0, 0), Vector2f(0, 0))
{
	this->Direction = Direction::Right;
	this->HealthPoints = MAX_PLAYER_HP;
	this->SpawnPoint = Vector2f(0, 0);
	this->Move = Move::None;
}
