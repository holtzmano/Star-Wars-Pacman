#pragma once
#include "BaseEnemy.h"
//-----------------------------------------------------------------------------

class Board;
//-----------------------Class StupidEnemy-------------------------------------
class SmartEnemy : public BaseEnemy
{
public:
	SmartEnemy(sf::Vector2f, sf::Vector2f);
	virtual void move(const Board&, float) override;

private:
	Direction getMinDistence(sf::Vector2f playerPos, sf::Vector2f left, sf::Vector2f, sf::Vector2f, bool, bool, bool, bool, sf::Vector2f);
	sf::Vector2f obsticalOvercome(sf::Vector2f pos, sf::Vector2f playerPos, const Board& board, bool& found, Direction&);
	sf::Vector2f findWay(sf::Vector2f, const Board&, Direction, Direction, sf::Vector2f, bool&);
	sf::Vector2f findCoordAtEnd(sf::Vector2f pos, Direction direc, const Board& board, sf::Vector2f);
	bool tryMove(Direction direc, sf::Vector2f& pos, const Board& board, float);
};