#include "..\include\GameObj.h"
//-----------------------------------------------------------------------------

GameObj::GameObj(const sf::Texture* texture, sf::Vector2f location, sf::Vector2f size):
	m_size(size)
{
	m_sprite.setTexture(*texture);
	m_sprite.setOrigin(texture->getSize().x / 2.f, texture->getSize().y / 2.f);
	m_sprite.setScale(m_size.x / m_sprite.getGlobalBounds().width, m_size.y / m_sprite.getGlobalBounds().height);
	m_sprite.setPosition(location);
}

//-----------------------------------------------------------------------------
void GameObj::draw(sf::RenderWindow& window) const
{
	window.draw(m_sprite);
}
//-----------------------------------------------------------------------------
sf::Vector2f GameObj::getPosition() const
{
	return m_sprite.getPosition();
}
//-----------------------------------------------------------------------------
void GameObj::setPosition(sf::Vector2f loc)
{
	m_sprite.setPosition(loc);
}
//-----------------------------------------------------------------------------
bool GameObj::collide(sf::FloatRect otherObj) const
{
	return m_sprite.getGlobalBounds().intersects(otherObj);
}
//-----------------------------------------------------------------------------
sf::Vector2f GameObj::getReach() const
{
	return m_size/2.0f;
}
//-----------------------------------------------------------------------------
sf::Vector2f GameObj::getSize() const
{
	return m_size;
}
//-----------------------------------------------------------------------------
sf::FloatRect GameObj::getGlobalBounds() {
	return m_sprite.getGlobalBounds();
}


