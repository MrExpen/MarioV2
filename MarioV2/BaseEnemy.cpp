#include "BaseEnemy.h"

BaseEnemy::BaseEnemy(Vector2f position, Vector2f speed, bool iskinematic, Vector2f size) : BaseEntity(iskinematic, true, size, position, speed)
{
	isAlive = true;
}

BaseEnemy::BaseEnemy(Vector2f position, Vector2f speed) : BaseEnemy(position, speed, true, Vector2f(32, 32))
{
}

BaseEnemy::BaseEnemy(Vector2f position) : BaseEnemy(position, Vector2f(0, 0), false, Vector2f(32, 32))
{
}

GameAction BaseEnemy::onPlayerEnter(Player& player)
{
	return player.TakeDamage();
}

void BaseEnemy::Die()
{
	//TODO
}

void BaseEnemy::Draw(RenderWindow& window)
{
	if (isAlive)
	{
		BaseEntity::Draw(window);
	}
}

BaseEnemy::~BaseEnemy()
{

}
