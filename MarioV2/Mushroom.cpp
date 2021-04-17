#include "Mushroom.h"

Mushroom::Mushroom(Vector2f position, vector<Texture*>* Textures) : BaseEnemy(position, Vector2f(DEFAULTSPEEDX, 0))
{
	Direction = Direction::Right;
	Way = 0;
	Timer = 0;

	this->Textures = Textures;
}

void Mushroom::UpdateX(float time)
{
	Timer += time;
	if (isAlive)
	{
		if (!canCollide && !isKinematic && Timer > MUSHROOM_DEAD_TIME)
		{
			isAlive = false;
		}
		Way += abs(Speed.x) * time;
		BaseEnemy::UpdateX(time);
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
	}
}

int Mushroom::GetTextureIndex()
{
	if (!canCollide && !isKinematic)
	{
		return 2;
	}
	return (int(Way) / WAY_TO_ACHIVE_MUSHROOM) % 2;
}
//FIXME
GameAction Mushroom::onPlayerEnter(Player& player)
{
	if (player.Speed.y < 0)
	{
		player.Speed.y = JUMP_KILL_SPEED;
		return GameAction::EnemyDie;
	}
	return player.TakeDamage();
}

void Mushroom::BuildSprite(Sprite& sprite)
{
	sprite.setTexture(*(*Textures)[GetTextureIndex()]);
	if (this->Direction == Direction::Left)
	{
		sprite.setScale(-1, 1);
		sprite.setOrigin(Size.x, 0);
	}
	sprite.setPosition(Position);
}
