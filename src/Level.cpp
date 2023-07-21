#include "..\include\Level.h"
#include <Board.h>
#include <fstream>
#include <Macros.h>
#include <io.h>
#include <iostream>
//-----------------------------------------------------------------------------
Level::Level(std::ifstream& board)
{
	board >> m_size.y >> m_size.x >> m_time;
	board.ignore(1);
	std::string str;
	for (int row = 0; row < m_size.y; ++row)
	{
		getline(board, str);
		m_levelMap.push_back(str);
	}
	board.get();
}

//-----------------------------------------------------------------------------
//this function returns the map's size
sf::Vector2i Level::getMapSize() const
{
	return m_size;
}

//-----------------------------------------------------------------------------
//returns the char of the location given
char Level::getChar(int row, int col) const
{
	return (!inMap(row,col)) ? WALL : m_levelMap[row][col];
}
float Level::getTime() const
{
	return m_time;
}
//-----------------------------------------------------------------------------
//returns true if the row and col in the parameters in on the map
bool Level::inMap(int row, int col)const
{
	return (row >= 0) && (row < m_size.y) && (col >= 0) && (col < m_size.x);
}

