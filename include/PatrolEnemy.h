#pragma once
#include <BaseEnemy.h>
//-----------------------------------------------------------------------------
class Board;
//-----------------------------------------------------------------------------
class PatrolEnemy : public BaseEnemy
{
public:
	PatrolEnemy(sf::Vector2f, sf::Vector2f);
	virtual void move(const Board& control, float dt);

private:
	Direction m_directionX = (Direction)(rand() % 2);	//randomly sets directon to left or right
	bool willFall(const Board& control, sf::Vector2f loc) const;
};

