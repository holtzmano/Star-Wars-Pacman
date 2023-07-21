#pragma once
#include <MovingObj.h>
//-----------------------------------------------------------------------------

class Board;
//-----------------------------Class Player----------------------------------
class Player : public MovingObj
{
public:
	Player(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void move(const Board&, float) override;
};