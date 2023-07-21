#pragma once
#include "BaseEnemy.h"
//---------------Classes and structs used--------------------------------------
class Board;
//-----------------------Class StupidEnemy-------------------------------------
class StupidEnemy: public BaseEnemy
{
public:
	StupidEnemy(sf::Vector2f , sf::Vector2f);
	virtual void move(const Board&, float) override;
};

