#include "Mushroom.h"

Mushroom::Mushroom(Vector2f position) : BaseEnemy(position, Vector2f(DEFAULTSPEEDX, 0))
{
}
//FIXME
GameAction Mushroom::onPlayerEnter(Player& player)
{
	if (player.Speed.y < 0)
	{
		player.Speed.y = JUMP_KILL_SPEED;
		return GameAction::EnemyDie;
	}
	return player.TakeDamage();
}

Mushroom::~Mushroom()
{
}
