#pragma once
#include <Bonus.h>
//-----------------------------------------------------------------------------

class TimeBonus : public Bonus
{
public:
	TimeBonus(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void collect(Controller&) override;
};