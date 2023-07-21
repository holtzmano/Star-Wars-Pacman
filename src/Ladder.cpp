#include "..\include\Ladder.h"
#include <Textures.h>
//-----------------------------------------------------------------------------

Ladder::Ladder(sf::Vector2f location, sf::Vector2f size):
	StaticObj(&Textures::instance().getTexture(5), location, size)
{}