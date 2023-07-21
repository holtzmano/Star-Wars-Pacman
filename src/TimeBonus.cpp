#include "..\include\TimeBonus.h"
#include <Controller.h>
//-----------------------------------------------------------------------------

TimeBonus::TimeBonus(sf::Vector2f pos, sf::Vector2f size):
	Bonus(pos, size)
{}
//-----------------------------------------------------------------------------
void TimeBonus::collect(Controller& control)
{
	Music::instance().playTimeBonus();
	control.addTime();
	toggleRemove();
}
