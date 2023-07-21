#include "..\include\StaticObj.h"
//-----------------------------------------------------------------------------

StaticObj::StaticObj(const sf::Texture* texture, sf::Vector2f location, sf::Vector2f size):
	GameObj(texture, location, size)
{
	//m_myObj = objChar;
}
//-----------------------------------------------------------------------------
void StaticObj::draw(sf::RenderWindow& window) const
{
	if (!m_removed)
		GameObj::draw(window);
}
//-----------------------------------------------------------------------------
void StaticObj::toggleRemove() {
	m_removed = !m_removed;
}
//-----------------------------------------------------------------------------
bool StaticObj::isRemoved() const
{
	return m_removed;
}
