#include "..\include\Player.h"
#include <Board.h>
#include <Textures.h>

//-----------------------------------------------------------------------------

Player::Player(sf::Vector2f pos, sf::Vector2f size):
	MovingObj(&Textures::instance().getTexture(0), pos, size)
{
	m_speed = 190.f;
}

//-----------------------------------------------------------------------------
void Player::move(const Board& board, float dt) 
{
	auto speed = m_speed;
	speed *= dt;
	sf::Vector2f newPos = getPosition();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_direction = up;
		newPos.y -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_direction = down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		m_direction = left;
		newPos.x -= speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		m_direction = right;
		newPos.x += speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
		board.dig({ newPos.x + (getReach().x * 2), newPos.y + (getReach().y * 2) });
		return;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
		board.dig({ newPos.x - (getReach().x * 2), newPos.y + (getReach().y * 2) });
		return;
	}
	else
		m_direction = stop;

	MovingObj::move(board, speed);
	if (m_direction == down) {
		newPos = getPosition();
		newPos.y += speed;
	}
	if(isValidMove(board,newPos, speed))
		m_sprite.setPosition(newPos);
}




