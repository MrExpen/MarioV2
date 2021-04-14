#include <SFML/Graphics.hpp>
#include "BaseEntity.h"

using namespace sf;

void BaseEntity::Draw(RenderWindow& window)
{
	auto tmp = GetSprite();
	window.draw(*tmp);
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
	Position.y -= Speed.y * time;
}

int BaseEntity::GetTextureIndex()
{
	return 0;
}

Drawable* BaseEntity::GetSprite()
{
	auto rectangleShape = new RectangleShape(Size);
	rectangleShape->setFillColor(Color::Black);
	rectangleShape->setPosition(Position);
	return rectangleShape;

	//TODO

	Sprite* sprite = new Sprite(*Textures[GetTextureIndex()]);
	return sprite;
}

BaseEntity::BaseEntity(bool iskinematic, bool cancollide, Vector2f size, Vector2f position, Vector2f speed)
{
	isKinematic = iskinematic;
	canCollide = cancollide;
	Size = size;
	Position = position;
	Speed = speed;
}
