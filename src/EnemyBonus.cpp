#include "..\include\EnemyBonus.h"
#include <Controller.h>
EnemyBonus::EnemyBonus(sf::Vector2f pos, sf::Vector2f size):
	Bonus(pos, size)
{}
//-----------------------------------------------------------------------------
void EnemyBonus::collect(Controller& control)
{
	Music::instance().playEnemyBonus();
	control.addEnemy();
	toggleRemove();
}
