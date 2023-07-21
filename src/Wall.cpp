#include "..\include\Wall.h"
#include <SFML/Graphics.hpp>
#include <Textures.h>
//-----------------------------------------------------------------------------

Wall::Wall(sf::Vector2f pos, sf::Vector2f size):
	StaticObj(&Textures::instance().getTexture(3),pos,size)
{}
//-----------------------------------------------------------------------------
bool Wall::checkTimer(float elapsed)
{
	if (m_removed && (m_timer -= elapsed) < 0) {
		m_removed = false;
		m_empty = true;
		m_timer = 3.f;
		return true;
	}
	return false;
}
//-----------------------------------------------------------------------------
void Wall::fill()
{
	m_empty = false;
}
//-----------------------------------------------------------------------------
bool Wall::isEmpty() const
{
	return m_empty;
}


