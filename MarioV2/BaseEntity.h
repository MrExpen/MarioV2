#include <SFML/Graphics.hpp>

#define g 9.8

using namespace sf;

class BaseEntity
{
public:
	BaseEntity();
	BaseEntity(Sprite sprite, Vector2f position, bool isKinematic);
	~BaseEntity();
	Sprite sprite;
	bool isKinematic;
	bool onGround;
	float speedx;
	float speedy;
	void Update(float& time);
	void Draw(RenderWindow& window);

private:

};

void BaseEntity::Update(float& time)
{
	if (!isKinematic)
		return;
	if (onGround)
		return;
	speedy = speedy + g * time;
	sprite.move(0, speedy * time);
}

void BaseEntity::Draw(RenderWindow& window)
{
	window.draw(sprite);
}

BaseEntity::BaseEntity()
{
}


BaseEntity::BaseEntity(Sprite sprite, Vector2f position, bool isKinematic)
{
	this->sprite = sprite;
	sprite.setPosition(position);
	this->isKinematic = isKinematic;
}


BaseEntity::~BaseEntity()
{
}

