#pragma once
#include <StaticObj.h>
//-----------------------------------------------------------------------------

class Controller;
//-----------------------------------------------------------------------------

class Coin : public StaticObj
{
public:
	Coin(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	void collect(Controller&);
};
