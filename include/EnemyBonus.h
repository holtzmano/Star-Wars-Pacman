#pragma once
#include <Bonus.h>
//-----------------------------------------------------------------------------
class EnemyBonus : public Bonus
{
public:
	EnemyBonus(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void collect(Controller&) override;
};