#pragma once
#include <Bonus.h>
//-----------------------------------------------------------------------------

class LifeBonus : public Bonus
{
public:
	LifeBonus(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void collect(Controller&) override;
};