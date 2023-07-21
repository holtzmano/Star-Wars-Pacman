#include "..\include\Textures.h"
#include <iostream>
//-----------------------------------------------------------------------------

Textures::Textures()
{
	std::string pictureNames[] = { "LukeSheet.png", "STS.png", "Coin.png",
								   "wall2.png", "rail.png", "ladder.png", "blueDeathStar.png"						
									,"Box.png",  "MandoBack.png", "stars.png", "lukeMightFall.png" };
	sf::Texture texture = sf::Texture();

	for (auto& pictureName : pictureNames)
	{
		texture.loadFromFile(pictureName);
		m_textures.push_back(texture);	
	}
}
//-----------------------------------------------------------------------------

Textures& Textures::instance() {
	static Textures inst;
	return inst;
}
//-----------------------------------------------------------------------------

const sf::Texture& Textures::getTexture(int ind) const
{
	return m_textures[ind];
}


