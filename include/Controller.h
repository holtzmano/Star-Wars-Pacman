#pragma once
#include "Level.h"
#include <iostream>
#include <fstream>
#include "Macros.h"
#include "Menu.h"
#include "Music.h"
#include "Textures.h"
#include "Board.h"
//-----------------------------------------------------------------------------
using vectorLevel = std::vector<std::unique_ptr<Level>>;

class Controller
{
public:
	Controller();
	void run();
	void addCoin();
	void addPoints();
	void addTime();
	void addLife();
	void addEnemy();

private:
	bool startGame();
	void readLevels();
	void reduceNumOfCoins();
	sf::RenderWindow m_window = sf::RenderWindow(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "Lode Runner");
	Board m_board;
	sf::Clock m_gameClock;
	float m_timeRemaining;
	Menu m_menu;
	sf::Vector2u m_windowSize = m_window.getSize();
	vectorLevel m_levels;
	unsigned m_gameLevel = 0;
	unsigned m_score = 0;
	unsigned m_lives = LIVES;
	unsigned m_coinsRemaining = 0;
	std::vector<sf::Text> m_statusInfo;
	sf::Font m_font;
	void initializeTexts();
	void setText(sf::Text& message, std::string str, sf::Vector2f pos);
	void updateData();
	void drawStatus();
};