#pragma once
//-----------------------------------------------------------------------------

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
//-----------------------------------------------------------------------------
class Level
{
public:
	Level(std::ifstream&);
	sf::Vector2i getMapSize() const; 
	char getChar(int, int) const;
	float getTime() const;
	bool inMap(int, int) const;

private: 
	std::vector<std::string> m_levelMap;
	sf::Vector2i m_size;
	float m_time;
};
