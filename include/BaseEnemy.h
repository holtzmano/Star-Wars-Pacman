#pragma once
#include "MovingObj.h"
//-----------------------------------------------------------------------------
class BaseEnemy : public MovingObj
{
public:
	BaseEnemy(sf::Vector2f , sf::Vector2f);
	virtual void move(const Board&, float) = 0;
protected:
	std::vector<sf::Vector2f> getMoveOptions(float) const;
};