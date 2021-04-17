#include "Wall.h"

Wall::Wall(Vector2f position, int textureIndex, vector<Texture*>* Textures) : BaseEntity(false, true, Vector2f(32, 32), position, Vector2f(0, 0))
{
	TextureIndex = textureIndex;
	this->Textures = Textures;
}

void Wall::BuildSprite(Sprite& sprite)
{
	sprite.setTexture(*(*Textures)[TextureIndex]);
	sprite.setPosition(Position);
}
