#include <SFML/Graphics.hpp>
#include "BaseEntity.h"

using namespace sf;

void BaseEntity::Draw(RenderWindow& window)
{
	Sprite sprite;
	BuildSprite(sprite);
	window.draw(sprite);
}

bool BaseEntity::isIntersect(BaseEntity& entity)
{
	return (entity.Position.y - Position.y < Size.y&& Position.y - entity.Position.y < entity.Size.y) && (entity.Position.x - Position.x < Size.x&& Position.x - entity.Position.x < entity.Size.x) && canCollide && entity.canCollide;
}

void BaseEntity::UpdateX(float time)
{
	if (!isKinematic)
		return;
	Position.x += Speed.x * time;
}

void BaseEntity::UpdateY(float time)
{
	if (!isKinematic)
		return;

	Speed.y -= ACCELERATION_Y * time;
	Position.y -= Speed.y * time;
	if (Speed.y > MAX_SPEED_Y)
	{
		Speed.y = MAX_SPEED_Y;
	}
	else if (Speed.y < MIN_SPEED_Y)
	{
		Speed.y = MIN_SPEED_Y;
	}
}

int BaseEntity::GetTextureIndex()
{
	return 0;
}

void BaseEntity::BuildSprite(Sprite& sprite)
{
	RectangleShape rectangleshape(Size);
	rectangleshape.setFillColor(Color::Magenta);
	sprite.setTexture(*rectangleshape.getTexture());
}

BaseEntity::BaseEntity(bool iskinematic, bool cancollide, Vector2f size, Vector2f position, Vector2f speed)
{
	isKinematic = iskinematic;
	canCollide = cancollide;
	Size = size;
	Position = position;
	Speed = speed;
}
