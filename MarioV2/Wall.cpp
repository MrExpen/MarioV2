#include "Wall.h"

Wall::Wall(Vector2f position, int textureIndex) : BaseEntity(false, true, Vector2f(32, 32), position, Vector2f(0, 0))
{
	TextureIndex = textureIndex;
	for (int i = 0; i < 7; i++)
	{
		Texture* texture = new Texture();
		texture->loadFromFile("Images\\Walls.png", IntRect(i * 32, 0, 32, 32));
		Textures.push_back(texture);
	}
}

Drawable* Wall::GetSprite()
{
	Sprite* sprite = new Sprite(*Textures[TextureIndex]);
	sprite->setPosition(Position);
	return sprite;
}

Wall::~Wall()
{
}
