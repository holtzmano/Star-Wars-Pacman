#include "..\include\LifeBonus.h"
#include <Controller.h>
//-----------------------------------------------------------------------------

LifeBonus::LifeBonus(sf::Vector2f pos, sf::Vector2f size):
	Bonus(pos, size)
{}
//-----------------------------------------------------------------------------

void LifeBonus::collect(Controller& control)
{
	Music::instance().playLifeBonus();
	control.addLife();
	toggleRemove();
}
