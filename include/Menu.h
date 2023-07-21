#pragma once
#include <SFML/Graphics.hpp>
//-----------------------------------------------------------------------------

class Menu
{
public:
	Menu();
	void resetMainMenu(sf::RenderWindow&);
	bool runMenu(sf::RenderWindow& window, bool, bool) ;

private:
	void drawMywindow(sf::RenderWindow& window) const;
	void setMyscreen(bool hasWon);
	void setText(sf::Text& message, std::string str, sf::Vector2f pos);
	void stopMusic();
	bool isClickedOn(const sf::Text&, const sf::Vector2f& pos) const;
	sf::Text m_enter;
	sf::Text m_exit;
	sf::Font m_font;
	sf::Sprite m_backGround;
	sf::Text m_mainMsg;
};