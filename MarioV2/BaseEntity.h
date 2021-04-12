#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class BaseEntity
{
public:
	bool isKinematic;
	bool canCollide;
	Vector2f position;
	Vector2f spead;
	virtual void Update(float time);
	virtual void Draw(RenderWindow& window);
};

