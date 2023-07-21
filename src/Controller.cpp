#include "Controller.h"

//Constructor
Controller::Controller(): m_board (Board (m_gameClock))
{
	m_window.setFramerateLimit(60);
	readLevels();
	m_font.loadFromFile("StarJediHollow-A4lL.ttf");
}
//-----------------------------------------------------------------------------
/*
this function is the function that starts the game and is called from main.cpp
it will run the menu window in a loop while calling for the function that plays
the game startGame.
*/
void Controller::run() {
	bool finished = false;
	bool hasWon = false;
	while (true)
	{
		if (m_menu.runMenu(m_window, finished, hasWon))
		{
			Music::instance().playGame();
			m_lives = LIVES;
			m_score = 0;
			m_gameLevel = 0;
			m_board.loadLevel(m_levels[m_gameLevel].get());
			m_coinsRemaining = m_board.getCoinAmount();
			m_timeRemaining = m_board.getLevelTime();
			initializeTexts();

			if (startGame()) //starts the game, returns if player won or lost
				hasWon = true;
			finished = true;
			if (m_menu.runMenu(m_window, finished, hasWon))
			{
				m_menu.resetMainMenu(m_window);
				hasWon = false;
				finished = false;
				continue;
			}
			break;
		}
		else
			break;
	}
	m_window.close();
}

//-----------------------------------------------------------------------------
/*
boolean function that returns true if player beat the game and false if not.
this is the main function that starts the game sequence.
*/
bool Controller::startGame()
{
		auto isPlaying = false;
		m_gameClock.restart(); 
	
		while (m_window.isOpen())
		{
			for (auto event = sf::Event{}; m_window.pollEvent(event); )
			{
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					m_window.close();
					break;
				}
				if (!isPlaying && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					isPlaying = true;
					m_gameClock.restart(); 
				}
			}
			if (isPlaying) {
				if (m_gameClock.getElapsedTime().asSeconds() >= 0.02f) {
					float dt = m_gameClock.restart().asSeconds();
					m_timeRemaining -= dt;
					if (dt > 1)
						continue;
					m_board.move(dt);
					if ((int)m_timeRemaining == 0 || m_board.checkEnemyCollisions()) {
						if ((int)m_timeRemaining == 0)
							Music::instance().playBuzzer();

						m_lives--;
						if (!m_lives)
						{
							Music::instance().stopGame();
							return false;
						}
						m_board.restartLevel();
						m_coinsRemaining = m_board.getCoinAmount();
						m_timeRemaining = m_board.getLevelTime();
						isPlaying = false;
					}
					m_board.collectObj(*this);
					if (!m_coinsRemaining) {
						m_score += 50 * (m_gameLevel + 1);
						m_gameLevel++;
						if (m_gameLevel == m_levels.size()) {	
							Music::instance().stopGame();	
							return true;
						}
						
						m_board.loadLevel(m_levels[m_gameLevel].get());
						m_coinsRemaining = m_board.getCoinAmount();
						m_timeRemaining = m_board.getLevelTime();
						isPlaying = false;
					}
				}
			}
			m_window.clear();
			m_board.render(m_window);
			drawStatus();
			m_window.display();
		}
}

//-----------------------------------------------------------------------------
/*This Function reads the maps from "Board.txt" and creates a level for each 
map each level is stored in a vector of levels. each level holds the specific 
data of that level
*/
void Controller::readLevels()
{
	std::ifstream board;
	board.open("Board.txt");
	if (board.is_open())
	{
		for (int level = 0; !board.fail(); ++level)
			m_levels.push_back(std::make_unique<Level>(Level(board)));
		board.close();
	}
	else
		std::cerr << "Error opening file";
}
//-----------------------------------------------------------------------------
void Controller::addCoin()
{
	m_score += 2 * (m_gameLevel + 1);
	m_coinsRemaining--;
}
//-----------------------------------------------------------------------------
void Controller::addPoints()
{
	 m_score += 50*(m_gameLevel+1);
}
//-----------------------------------------------------------------------------
void Controller::addTime()
{
	m_timeRemaining += 30.f;
}
//-----------------------------------------------------------------------------
void Controller::addLife()
{
	m_lives++;
}
//-----------------------------------------------------------------------------
void Controller::addEnemy()
{
	m_board.addEnemy();
}
//-----------------------------------------------------------------------------
void Controller::reduceNumOfCoins()
{
	m_coinsRemaining--;
}
//-----------------------------------------------------------------------------
/*
Initializes texts of the current game status.
*/
void Controller::initializeTexts()
{
	m_statusInfo.resize(9);
	setText(m_statusInfo[0], "Level: ", { LEVEL_TEXT_X_POS, INFO_MENU_TEXTS_Y_POS });
	setText(m_statusInfo[1], "Score: ", { SCORE_TEXT_X_POS, INFO_MENU_TEXTS_Y_POS });
	setText(m_statusInfo[2], "Lives: ", { LIVES_TEXT_X_POS, INFO_MENU_TEXTS_Y_POS });
	setText(m_statusInfo[3], "Time Left: ", { TIME_TEXT_X_POS, INFO_MENU_TEXTS_Y_POS });
	setText(m_statusInfo[8], "Press space to start", { SPACE_TO_START, INFO_MENU_TEXTS_Y_POS });
	m_statusInfo[4] = m_statusInfo[0];
	m_statusInfo[5] = m_statusInfo[1];
	m_statusInfo[6] = m_statusInfo[2];
	m_statusInfo[7] = m_statusInfo[3];
	updateData();
}
//-----------------------------------------------------------------------------

void Controller::setText(sf::Text& message, std::string str, sf::Vector2f pos)
{
	message.setFont(m_font);
	message.setString(str);
	message.setPosition(pos);
	message.setCharacterSize(INFO_MENU_TEXT_SIZE);
	message.setFillColor(sf::Color::Yellow);
}
//-----------------------------------------------------------------------------
/*
updates the current game information e.g. current score, lives, time and level 
*/
void Controller::updateData()
{
	m_statusInfo[4].setString(m_statusInfo[0].getString() + std::to_string(m_gameLevel + 1));
	m_statusInfo[5].setString(m_statusInfo[1].getString() + std::to_string(m_score));
	m_statusInfo[6].setString(m_statusInfo[2].getString() + std::to_string(m_lives));
	if(m_timeRemaining >= 0)
		m_statusInfo[7].setString(m_statusInfo[3].getString() + std::to_string((int)m_timeRemaining));
	else
		m_statusInfo[7].setString(m_statusInfo[3].getString() + "--");
}
//-----------------------------------------------------------------------------
void Controller::drawStatus() {
	updateData();
	auto rec = sf::RectangleShape({WIN_WIDTH, INFO_MENU_HEIGHT});
	rec.setPosition({0, WIN_HEIGHT - INFO_MENU_HEIGHT-1 });
	rec.setFillColor(sf::Color::Black);
	m_window.draw(rec);
	for (int i = 4; i < m_statusInfo.size(); i++)
		m_window.draw(m_statusInfo[i]);
}