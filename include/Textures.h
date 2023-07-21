#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
//-----------------------------------------------------------------------------

class Textures
{
public:
	static Textures& instance();
	const sf::Texture& getTexture(int) const;

private:
	Textures();
	Textures& operator=(const Textures&) = default;
	std::vector<sf::Texture> m_textures;
};