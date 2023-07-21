#pragma once
#include <StaticObj.h>
//-----------------------------------------------------------------------------

class Wall : public StaticObj
{
public:
	Wall(sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	bool checkTimer(float elapsed);
	void fill();
	bool isEmpty()const;

private:
	float m_timer = 3.f;
	bool m_empty = true;
};
