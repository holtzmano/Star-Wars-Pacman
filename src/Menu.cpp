#include "..\include\Menu.h"
#include <Macros.h>
#include <Music.h>
#include <Textures.h>
//-----------------------------------------------------------------------------

Menu::Menu()
{
	m_font.loadFromFile("StarJedi-DGRW.ttf");
	m_backGround = sf::Sprite(Textures::instance().getTexture(8));
	m_backGround.setScale({ WIN_WIDTH / m_backGround.getGlobalBounds().width, WIN_HEIGHT / m_backGround.getGlobalBounds().height });
	setText(m_mainMsg, "lode runner - star wars edition", { MAIN_MSG_WIDTH, MAIN_MSG_HEIGHT });
	setText(m_enter, "new game", { ENTER_WIDTH, ENTER_HEIGHT});
	setText(m_exit, "quit", { EXIT_WIDTH, EXIT_HEIGHT });
}																			
//---------------------------------------------------------------------------------------------
bool Menu::runMenu(sf::RenderWindow& window, bool finished, bool hasWon)
{
	window.clear();
	if (finished)
	{
		setMyscreen(hasWon);
		setText(m_enter, "main menu", { ENTER_WIDTH, ENTER_HEIGHT2 });
	}
	drawMywindow(window);
	window.display();
	if(!finished)
		Music::instance().playMenu();

	while (window.isOpen())
		for (auto event = sf::Event{}; window.waitEvent(event);)
			switch (event.type)
			{
			case sf::Event::Closed:
				stopMusic();
				return false;
			case sf::Event::MouseButtonReleased:
				auto location = window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y });

				if (isClickedOn(m_enter, location))
				{
					stopMusic();
					return true;
				}
				if (isClickedOn(m_exit, location))
				{
					stopMusic();
					return false;
				}
			}
	return false;
}

//---------------------------------------------------------------------------------------------
void Menu::resetMainMenu(sf::RenderWindow& window)
{
	setText(m_mainMsg, "lode runner - star wars edition", { MAIN_MSG_WIDTH, MAIN_MSG_HEIGHT });
	setText(m_enter, "new game", { ENTER_WIDTH, ENTER_HEIGHT });
	m_backGround = sf::Sprite(Textures::instance().getTexture(8));
	m_backGround.setScale({ WIN_WIDTH / m_backGround.getGlobalBounds().width, WIN_HEIGHT / m_backGround.getGlobalBounds().height });
}

//---------------------------------------------------------------------------------------------
void Menu::drawMywindow(sf::RenderWindow& window) const
{
	window.draw(m_backGround);
	window.draw(m_mainMsg);
	window.draw(m_enter);
	window.draw(m_exit);
}

//---------------------------------------------------------------------------------------------
void Menu::setMyscreen(bool hasWon)
{
	if (hasWon)
	{
		Music::instance().playWonGame();
		m_backGround = sf::Sprite(Textures::instance().getTexture(9));
		m_backGround.setScale({ WIN_WIDTH / m_backGround.getGlobalBounds().width, WIN_HEIGHT / m_backGround.getGlobalBounds().height });
		setText(m_mainMsg, "you won!", { ENTER_WIDTH, MAIN_MSG_HEIGHT2 });
	}
	else
	{
		Music::instance().playLostGame();
		m_backGround = sf::Sprite(Textures::instance().getTexture(10));
		m_backGround.setScale({ WIN_WIDTH / m_backGround.getGlobalBounds().width, WIN_HEIGHT / m_backGround.getGlobalBounds().height });
		setText(m_mainMsg, "game over!", { MAIN_MSG_WIDTH2, MAIN_MSG_HEIGHT3 });
	}
}

//---------------------------------------------------------------------------------------------
void Menu::setText(sf::Text& message, std::string str, sf::Vector2f pos)
{
	message.setFont(m_font);
	message.setString(str);
	message.setPosition(pos);
	message.setCharacterSize(WIN_WIDTH / 20);
	message.setFillColor(sf::Color(192, 192, 192, 255));
}
//---------------------------------------------------------------------------------------------
void Menu::stopMusic()
{
	Music::instance().stopWonGame();
	Music::instance().stopMenu();
	Music::instance().stopLostGame();
}

//---------------------------------------------------------------------------------------------
//checks if the specific message sent has been clicked on or not
bool Menu::isClickedOn(const sf::Text& text, const sf::Vector2f& pos) const
{
	return text.getGlobalBounds().contains(pos);
}

