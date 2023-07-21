#include "..\include\StupidEnemy.h"
#include <Board.h>
//-----------------------------------------------------------------------------

StupidEnemy::StupidEnemy(sf::Vector2f location, sf::Vector2f size) :
	BaseEnemy(location, size)
{
	m_speed = 200.f;
}
//-----------------------------------------------------------------------------
void StupidEnemy::move(const Board& control, float dt) {
	auto location = m_sprite.getPosition();
	auto speed = m_speed;
	speed *= dt;
	MovingObj::move(control, dt);
	auto options = getMoveOptions(speed);
	
	if (m_direction == down && isValidMove(control, options[down], speed)) {
		m_sprite.setPosition(options[down]);
		return;
	}
	srand(time(NULL));
	std::vector< sf::Vector2f> validMoves;
	for (int i = 0; i < 4; i++)
	{
		m_direction = (Direction)i;
		if (isValidMove(control, options[i], speed))
			validMoves.push_back(options[i]);
		else
			validMoves.push_back(m_sprite.getPosition());
	}
	if (validMoves.size()) {
		m_direction = (Direction)(rand() % validMoves.size());
		m_sprite.setPosition(validMoves[m_direction]);
	}
	else
		m_direction = stop;
}