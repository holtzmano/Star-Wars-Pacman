#pragma once
#include <GameObj.h>
#include <SFML/Graphics.hpp>
//-----------------------------------------------------------------------------

class StaticObj : public GameObj 
{
public:
	StaticObj(const sf::Texture*,sf::Vector2f location = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void draw(sf::RenderWindow& window) const override ;
	void toggleRemove();
	bool isRemoved() const;

protected:
	bool m_removed = false;
};