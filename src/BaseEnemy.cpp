#include "BaseEnemy.h"
#include <Textures.h>
//-----------------------------------------------------------------------------
BaseEnemy::BaseEnemy(sf::Vector2f location, sf::Vector2f size) :
	MovingObj(&Textures::instance().getTexture(1), location, size)
{}

//-----------------------------------------------------------------------------
/*
These are all the options that ALL the enemies have to move to.
*/
std::vector<sf::Vector2f> BaseEnemy::getMoveOptions(float speed) const{
	auto location = getPosition();
	return { {location.x + speed, location.y},
			{location.x - speed, location.y},
			{location.x, location.y + speed},
			{location.x, location.y - speed},
			location };
}