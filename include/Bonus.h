#pragma once
#include <StaticObj.h>
//-----------------------------------------------------------------------------

class Controller;
//-----------------------------------------------------------------------------

class Bonus : public StaticObj
{
public:
	Bonus(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void collect(Controller&) = 0;
};