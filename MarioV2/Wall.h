#pragma once
#include "BaseEntity.h"

class Wall :
    public BaseEntity
{
public:
    Wall(Vector2f position, int textureIndex, vector<Texture*>* Textures);
    int TextureIndex;
    virtual void BuildSprite(Sprite& sprite) override;
    ~Wall();
};

