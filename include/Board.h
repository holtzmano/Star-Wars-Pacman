#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>
#include <Menu.h>
//-----------------------------------------------------------------------------
class Level;
class StaticObj;
class MovingObj;
class Bonus;
class BaseEnemy;
class Controller;
class Wall;
//-----------------------------------------------------------------------------
class Board
{
public:
	Board(sf::Clock& clock);
	virtual ~Board();
	void addEnemy();
	void render(sf::RenderWindow&) const;
	float getLevelTime() const;
	char getCharAtLocation(sf::Vector2f location)const;
	bool inWindow(sf::Vector2f location) const;
	sf::Vector2f getObjLocation(sf::Vector2f) const;
	sf::Vector2i getIndexAtPos(sf::Vector2f) const;
	sf::Vector2i getLevelSize() const;
	sf::Vector2f getCoordinates(int, int)const;
	void dig(sf::Vector2f pos) const;
	int getCoinAmount() const;
	void loadLevel(Level* level);
	void move(float dt);
	void collectObj(Controller& control);
	bool hole(sf::Vector2f pos) const;
	bool checkEnemyCollisions() const;
	void restartLevel();
	sf::Vector2f getPlayerPos()const;

private:
	void wallReturned(Wall* wall);
	sf::Vector2f m_cellSize = {30.f, 30.f};
	std::vector<std::vector<std::unique_ptr<StaticObj>>> m_staticObjs;
	std::vector<std::unique_ptr<MovingObj>> m_movingObjs;
	Bonus* raffleBonus(sf::Vector2f) const;
	BaseEnemy* raffleEnemy(sf::Vector2f pos) const;
	sf::Sprite m_backGround;
	Level* m_level = NULL;
	int m_numOfCoins = 0;
	int m_numOfEnemies = 0;
	sf::Clock& m_clock;
};
