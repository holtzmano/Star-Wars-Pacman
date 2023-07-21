#pragma once
#include <Bonus.h>
//-----------------------------------------------------------------------------

class PointBonus : public Bonus
{
public:
	PointBonus(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void collect(Controller&) override;
};