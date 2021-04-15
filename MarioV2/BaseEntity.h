#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#define ACCELERATION_Y 0.1
#define MAX_SPEED_Y 100
#define MIN_SPEED_Y -MAX_SPEED_Y

using namespace std;
using namespace sf;

class BaseEntity
{
public:
	bool isKinematic;
	bool canCollide;
	Vector2f Size;
	Vector2f Position;
	Vector2f Speed;
	vector<Texture*> Textures;
	virtual void Draw(RenderWindow& window);
	virtual void UpdateX(float time);
	virtual void UpdateY(float time);
	virtual int GetTextureIndex();
	virtual Drawable* GetSprite();
	bool isIntersect(BaseEntity& entity);
	BaseEntity(bool iskinematic, bool cancollide, Vector2f size, Vector2f position, Vector2f speed);
};
