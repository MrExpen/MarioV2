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
	Timer += time;
	if (canCollide)
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
		Way += abs(Speed.x) * time;
	}
	else
	{
		if (Timer > PLAYER_DEAD_FLY_TIME)
		{
			Position = SpawnPoint;
			canCollide = true;
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
	{
		if (this->Direction != Direction::Right)
		{
			Way = 0;
		}
		this->Direction = Direction::Right;
	}
	else if (Speed.x < 0)
	{
		if (this->Direction != Direction::Left)
		{
			Way = 0;
		}
		this->Direction = Direction::Left;
	}
	else
	{
		Way = 0;
	}
}

void Player::BuildSprite(Sprite& sprite)
{
	sprite.setTexture(*(*Textures)[GetTextureIndex()]);
	if (this->Direction == Direction::Left)
	{
		sprite.setScale(-1, 1);
		sprite.setOrigin(Size.x, 0);
	}
	sprite.setPosition(Position);
}

int Player::GetTextureIndex()
{
	if (!canCollide)
		return 4;
	if (Speed.y != 0)
		return 3;
	if (Speed.x == 0)
	{
		return 0;
	}
	return (int(Way) / WAY_TO_ACHIVE) % 2 + 1;
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
Player::Player(Vector2f position, vector<Texture*>* Textures) : BaseEntity(true, true, Vector2f(24, 32), position, Vector2f(0, 0))
{
	this->Direction = Direction::Right;
	this->HealthPoints = MAX_PLAYER_HP;
	this->SpawnPoint = position;
	this->Move = Move::None;
	this->Textures = Textures;
	Way = 0;
	Timer = 0;
	LastHight = SpawnPoint.y;
}
//TODO: 32x32
Player::Player() : BaseEntity(true, true, Vector2f(24, 32), Vector2f(0, 0), Vector2f(0, 0))
{
	this->Direction = Direction::Right;
	this->HealthPoints = MAX_PLAYER_HP;
	this->SpawnPoint = Vector2f(0, 0);
	this->Move = Move::None;
	Way = 0;
	Timer = 0;
	LastHight = SpawnPoint.y;
}
