#include "Mushroom.h"

Mushroom::Mushroom(Vector2f position) : BaseEnemy(position, Vector2f(DEFAULTSPEEDX, 0))
{
	Direction = Direction::Right;
	Way = 0;

	for (int i = 0; i < 3; i++)
	{
		Texture* texture = new Texture();
		texture->loadFromFile("Images\\Mushroom.png", IntRect(i * 32, 0, 32, 32));
		Textures.push_back(texture);
	}
}

void Mushroom::UpdateX(float time)
{
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

int Mushroom::GetTextureIndex()
{
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

Drawable* Mushroom::GetSprite()
{
	Sprite* sprite = new Sprite(*Textures[GetTextureIndex()]);
	if (this->Direction == Direction::Left)
	{
		sprite->setScale(-1, 1);
		sprite->setOrigin(Size.x, 0);
	}
	sprite->setPosition(Position);
	return sprite;
}

Mushroom::~Mushroom()
{
}
