#include "..\include\Coin.h"
#include <Textures.h>
#include <Controller.h>

Coin::Coin(sf::Vector2f location, sf::Vector2f size):
	StaticObj(&Textures::instance().getTexture(2), location, size)
{}
//-----------------------------------------------------------------------------
void Coin::collect(Controller& control)
{
	Music::instance().playCoin();
	control.addCoin();
	toggleRemove();
}
