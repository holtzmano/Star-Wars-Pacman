#include "..\include\Bonus.h"
#include <Textures.h>
//-----------------------------------------------------------------------------
Bonus::Bonus(sf::Vector2f pos, sf::Vector2f size):
	StaticObj(&Textures::instance().getTexture(7),pos,size)
{}
