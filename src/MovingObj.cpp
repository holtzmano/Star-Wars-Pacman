#include "..\include\movingObj.h"
#include <Board.h>
#include <iostream>
#include <Textures.h>
//-----------------------------------------------------------------------------
MovingObj::MovingObj(const sf::Texture* texture, sf::Vector2f pos, sf::Vector2f size) :
	GameObj(texture, pos, { size.x, size.y - 2 }),
	m_direction(stop)
{
	auto rec = sf::IntRect(0, stop * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
	m_sprite.setTextureRect(rec);
	m_sprite.setOrigin({ rec.width / 2.f, rec.height / 2.f });
	m_sprite.setScale(size.x / m_sprite.getTextureRect().width, size.y / m_sprite.getTextureRect().height);
	m_sprite.setPosition(pos);
	m_startingPos = pos;
}
//-----------------------------------------------------------------------------
void MovingObj::draw(sf::RenderWindow& window) const
{
	GameObj::draw(window);
}
//-----------------------------------------------------------------------------
void MovingObj::move(const Board& control, float speed) {
	if (checkIfFalling(control, speed)) {
		m_direction = down;
	}
}
//-----------------------------------------------------------------------------
void MovingObj::resetPos()
{
	m_sprite.setPosition(m_startingPos);
}
//-----------------------------------------------------------------------------
/*
Checks if the object is falling
*/
bool MovingObj::checkIfFalling(const Board& control, float speed) {
	sf::Vector2f location = getPosition();
	auto reach = getReach();
	auto surrounding = getSurroundings({ location.x, location.y + speed }, control, speed);
	if ((((surrounding[leftBCorner] != WALL && surrounding[rightBCorner] != WALL) &&
		(surrounding[leftBCorner] != LADDER && surrounding[rightBCorner] != LADDER)) && surrounding[bottom] != RAIL)
		|| ((surrounding[leftBCorner] == RAIL || surrounding[rightBCorner] == RAIL) && surrounding[above] != RAIL))
	{
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
/*
Checks the surroundings at the desired new location the moving object wants to 
move to. returns true if is able to move there and false if not.
*/
bool MovingObj::isValidMove(const Board& control, sf::Vector2f& newLoc, float speed)
{
	if (!control.inWindow(newLoc))
		return false;
	sf::Vector2f prevLoc = m_sprite.getPosition(), ladderPos, reach = getReach();
	auto surrounding = getSurroundings(newLoc, control, speed);
	bool centered = false, valid = false;
	auto check = control.getObjLocation(prevLoc);
	m_onLadder = false;

	if (m_direction == left || m_direction == right) {
		if (surrounding[inFront] != WALL && surrounding[rightBCorner] != WALL &&
			surrounding[leftBCorner] != WALL && surrounding[topCorner] != WALL)
			valid = true;
		if (surrounding[inFront] == RAIL && surrounding[atFeet] == LADDER || 
		   (surrounding[inFront] == EMPTY && surrounding[leftBCorner] == WALL))
			newLoc.y = check.y;
		else {
			if (prevLoc.x != check.x) {
				m_sprite.setPosition({ check.x, prevLoc.y });
			}
		}
	}
	else if (m_direction == up) {
		if (surrounding[topCorner] == WALL)
			valid = false;
		else if (surrounding[atFeet] == LADDER) {
			m_onLadder = true;
			ladderPos = control.getObjLocation({ prevLoc.x, prevLoc.y + reach.y });
			if (prevLoc.x != ladderPos.x) {
				newLoc.x = ladderPos.x;
				newLoc.y += speed;
			}
			valid = true;
		}
	}
	else{
		if (surrounding[atFeetNew] == LADDER) {
			m_onLadder = true;
			if (surrounding[leftBCorner] == LADDER || surrounding[rightBCorner] == LADDER) {
				ladderPos = (surrounding[leftBCorner] == LADDER) ?
					control.getObjLocation({ newLoc.x - reach.x + speed, newLoc.y + reach.y }) :
					control.getObjLocation({ newLoc.x + reach.x - 1, newLoc.y + reach.y });
				if (newLoc.x != ladderPos.x) {
					newLoc.x = ladderPos.x;
					newLoc.y -= speed;
					centered = true;
				}
			}
		}
		if (surrounding[atFeetNew] == COIN || surrounding[atFeetNew] == RAIL ||
			((surrounding[leftBCorner] != WALL && surrounding[rightBCorner] != WALL) || centered))
			valid = true;
	}
	if (valid) {
		if (surrounding[atFeet] == WALL || surrounding[atFeetNew] == WALL ||
			(surrounding[atFeetNew] == EMPTY && surrounding[atFeet] == LADDER))
			newLoc.y = control.getObjLocation(newLoc).y;
		if (control.inWindow(newLoc))
			return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
//gets the characters surrounding the object
std::vector<char> MovingObj::getSurroundings(sf::Vector2f pos, const Board& control, float speed) const {
	std::vector<char> surroundings;
	auto reach = getReach();
	int sign = (m_direction == left) ? -1 : 1;
	sf::Vector2f positions[] = { { pos.x - reach.x - 1 + speed, pos.y + reach.y },
								 { pos.x + reach.x + 1 - speed, pos.y + reach.y },
								 { pos.x + sign * (reach.x + 1) - sign * speed, pos.y - reach.y + speed },
								 { pos.x + sign * (reach.x + 1), pos.y }, { pos.x, pos.y + reach.y },
								 { pos.x, pos.y + reach.y + speed},{ pos.x, pos.y + reach.y - speed},
								 {pos.x, pos.y - reach.y-1}};

	for (int i = 0; i <= above; i++)
		surroundings.push_back(control.getCharAtLocation(positions[i]));


	return surroundings;
}
//-----------------------------------------------------------------------------
void MovingObj::changeAnimation(float dt)
{
	auto size = getSize();
	m_animationTimer += dt;
	if (m_animationTimer >= m_nextAnimation) {
		m_animationTimer -= m_nextAnimation;
		if (m_animationCol == 3 || m_direction == stop)
			m_animationCol = 0;
		else
			m_animationCol++;

		if (m_onLadder && m_direction == down)
			m_direction = up;

		auto rec = sf::IntRect(m_animationCol * SPRITE_SIZE, m_direction * SPRITE_SIZE, SPRITE_SIZE, SPRITE_SIZE);
		m_sprite.setTextureRect(rec);
		m_sprite.setOrigin({ rec.width / 2.f, rec.height / 2.f });
		m_sprite.setScale(size.x / m_sprite.getTextureRect().width, size.y / m_sprite.getTextureRect().height);
	}
}
