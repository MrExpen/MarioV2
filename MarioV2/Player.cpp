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
	BaseEntity::UpdateX(time);
	if (Speed.x > MAX_PLAYER_SPEED_X)
	{
		Speed.x = MAX_PLAYER_SPEED_X;
	}
	else if (Speed.x < MIN_PLAYER_SPEED_X)
	{
		Speed.x = MIN_PLAYER_SPEED_X;
	}
}

void Player::UpdateY(float time)
{
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

Player::Player(Vector2f position) : BaseEntity(true, true, Vector2f(0, 0), position, Vector2f(0, 0))
{
	this->Direction = Direction::Right;
	this->HealthPoints = MAX_PLAYER_HP;
	this->SpawnPoint = position;
}

Player::Player() : BaseEntity(true, true, Vector2f(0, 0), Vector2f(0, 0), Vector2f(0, 0))
{
	this->Direction = Direction::Right;
	this->HealthPoints = MAX_PLAYER_HP;
	this->SpawnPoint = Vector2f(0, 0);
}
