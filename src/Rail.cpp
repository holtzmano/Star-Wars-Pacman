#include "..\include\Rail.h"
#include <Textures.h>
//-----------------------------------------------------------------------------

Rail::Rail(sf::Vector2f location, sf::Vector2f size):
	StaticObj(&Textures::instance().getTexture(4), location, size)
{}