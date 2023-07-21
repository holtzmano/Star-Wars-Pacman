#include "..\include\PointBonus.h"
#include <Controller.h>
//-----------------------------------------------------------------------------

PointBonus::PointBonus(sf::Vector2f pos, sf::Vector2f size):
	Bonus(pos, size)
{}
//-----------------------------------------------------------------------------
void PointBonus::collect(Controller& control)
{
	Music::instance().playScoreBonus();
	control.addPoints();
	toggleRemove();
}
