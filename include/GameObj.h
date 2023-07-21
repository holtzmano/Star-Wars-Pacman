#pragma once
#include <SFML/Graphics.hpp>
//-----------------------------------------------------------------------------
class GameObj 
{
public:
	GameObj(const sf::Texture* , sf::Vector2f , sf::Vector2f);
	virtual void draw(sf::RenderWindow& window) const;
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f);
	bool collide(sf::FloatRect) const;
	sf::Vector2f getReach()const;
	sf::Vector2f getSize()const;

	sf::FloatRect getGlobalBounds();

protected:
	sf::Sprite m_sprite;
private:
	sf::Vector2f m_size;
};