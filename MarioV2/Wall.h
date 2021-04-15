#pragma once
#include "BaseEntity.h"

class Wall :
    public BaseEntity
{
public:
    Wall(Vector2f position, int textureIndex);
    int TextureIndex;
    virtual Drawable* GetSprite() override;
    ~Wall();
};

