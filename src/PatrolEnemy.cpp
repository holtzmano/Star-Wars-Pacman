#include "..\include\PatrolEnemy.h"
#include <Board.h>
//-----------------------------------------------------------------------------

PatrolEnemy::PatrolEnemy(sf::Vector2f location, sf::Vector2f size) :
	BaseEnemy(location, size)
{
	m_speed = 200.f;
}

//-----------------------------------------------------------------------------
void PatrolEnemy::move(const Board& control, float dt)
{
	m_direction = m_directionX;
	auto location = m_sprite.getPosition();
	auto speed = m_speed;
	speed *= dt;
	MovingObj::move(control, speed);
	auto options = getMoveOptions(speed);
	if (m_direction == down) { //if falling (into hole)
		if (isValidMove(control, options[down], speed))
			m_sprite.setPosition(options[down]);
		m_direction = m_directionX;
		return;
	}
	if (isValidMove(control, options[m_direction], speed) && !willFall(control, options[m_direction]))
		m_sprite.setPosition(options[m_direction]);
	else
	{
		m_directionX == left ? m_directionX = right : m_directionX = left;	//changes direction
		m_direction = m_directionX;
		if (isValidMove(control, options[m_direction], speed))
			m_sprite.setPosition(options[m_direction]);
	}
}
//-----------------------------------------------------------------------------
//checks if at the next position the patrol will fall
bool PatrolEnemy::willFall(const Board& board, sf::Vector2f loc) const
{
	auto charBelow = board.getCharAtLocation({ loc.x, loc.y + getSize().y });
	if (charBelow != WALL && charBelow != LADDER && board.getCharAtLocation(loc)!=RAIL && !board.hole({ loc.x, loc.y + getSize().y }))
		return true;
	return false;
}


