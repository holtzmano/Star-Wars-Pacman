#include "..\include\Board.h"
#include <Player.h>
#include <Level.h>
#include <Macros.h>
#include <StaticObj.h>
#include <Windows.h>
#include <StupidEnemy.h>
#include <PatrolEnemy.h>
#include <SmartEnemy.h>
#include <Coin.h>
#include <Wall.h>
#include <Ladder.h>
#include <Rail.h>
#include <MovingObj.h>
#include <Bonus.h>
#include <LifeBonus.h>
#include <EnemyBonus.h>
#include <TimeBonus.h>
#include <PointBonus.h>
#include <Textures.h>
#include <Music.h>
#include <memory>
//-----------------------------------------------------------------------------
Board::Board(sf::Clock &clock): m_clock(clock)
{
	m_backGround = sf::Sprite(Textures::instance().getTexture(6));
	m_backGround.setScale({WIN_WIDTH / m_backGround.getGlobalBounds().width, WIN_HEIGHT / m_backGround.getGlobalBounds().height });
}

//-----------------------------------------------------------------------------
Board::~Board()
{}

//-----------------------------------------------------------------------------
void Board::render(sf::RenderWindow& window) const {
	window.draw(m_backGround);
	Wall* p;
	for (int i = 0; i < m_staticObjs.size(); i++)
		for (int j = 0; j < m_staticObjs[i].size(); j++) {
			if(m_staticObjs[i][j])
				m_staticObjs[i][j]->draw(window);
		}
	for (int j = 0; j < m_movingObjs.size(); j++)
		m_movingObjs[j]->draw(window);
}

//-----------------------------------------------------------------------------
void Board::wallReturned(Wall* wall)
{
	for (int i = 0; i < m_movingObjs.size(); i++) {
		if (wall->getGlobalBounds().intersects(m_movingObjs[i]->getGlobalBounds())) {
			auto pos = wall->getPosition();
			auto newPos = m_movingObjs[i]->getPosition();
			m_movingObjs[i]->setPosition({pos.x, newPos.y-abs(pos.y-m_cellSize.y- newPos.y)});
		}
	}
}

//-----------------------------------------------------------------------------
float Board::getLevelTime() const
{
	return m_level->getTime();
}

//-----------------------------------------------------------------------------
bool Board::inWindow(sf::Vector2f location) const {
	return location.x >= (m_cellSize.x / 2) - 1 && location.x <= WIN_WIDTH - m_cellSize.x / 2 - 1
		&& location.y >= m_cellSize.y / 2 - 1 && location.y <= (WIN_HEIGHT - INFO_MENU_HEIGHT) - m_cellSize.y / 2;
}

//-----------------------------------------------------------------------------
/*
Here we will load our level through the board.txt file.  We load into our data 
structures for moving(player & enemy) and non-moving objects(coin, wall...)
*/
void Board::loadLevel(Level* level)
{
	m_numOfEnemies = 0;
	m_numOfCoins = 0;
	m_level = level;
	char ch;
	auto size = level->getMapSize();
	m_movingObjs.clear();
	m_staticObjs.clear();
	m_staticObjs.resize(size.y);
	m_cellSize = { (float)WIN_WIDTH / size.x, ((float)WIN_HEIGHT - INFO_MENU_HEIGHT) /size.y };
	sf::Vector2f center = { m_cellSize/2.f}, location;
	m_movingObjs.push_back(nullptr);

	for (int i = 0; i < size.y; i++)
	{
		for (int j = 0; j < size.x; j++)
		{
			ch = level->getChar(i, j);
			location = { (float)j * m_cellSize.x + center.x-1, (float)i * m_cellSize.y + center.y-1};
			switch (ch)
			{
			case PLAYER:
				m_movingObjs[0] = std::make_unique<Player>(Player(location, m_cellSize));
				m_staticObjs[i].push_back(nullptr);
				break;
			case ENEMY:
				m_movingObjs.push_back(std::unique_ptr<BaseEnemy>(raffleEnemy(location)));
				m_staticObjs[i].push_back(nullptr);
				m_numOfEnemies++;
				break;
			case COIN:
				m_staticObjs[i].push_back(std::make_unique<Coin>(Coin(location, m_cellSize)));
				m_numOfCoins++;
				break;
			case WALL:
				m_staticObjs[i].push_back(std::make_unique<Wall>(Wall(location, m_cellSize)));
				break;
			case RAIL:
				m_staticObjs[i].push_back(std::make_unique<Rail>(Rail(location, m_cellSize)));
				break;
			case LADDER:
				m_staticObjs[i].push_back(std::make_unique<Ladder>(Ladder(location, m_cellSize)));
				break;
			case BONUS:
				m_staticObjs[i].push_back(std::unique_ptr<Bonus>(raffleBonus(location)));
				break;
			case EMPTY:
				m_staticObjs[i].push_back(nullptr);
			}
		}
	}
}
//-----------------------------------------------------------------------------
void Board::restartLevel()
{
	for (int i = 0; i < m_staticObjs.size(); i++)
		for (int j = 0; j < m_staticObjs[i].size(); j++) {
			if (m_staticObjs[i][j] && m_staticObjs[i][j]->isRemoved())
				m_staticObjs[i][j]->toggleRemove();
		}
	m_movingObjs.resize(m_numOfEnemies+1);
	for (int i = 0; i < m_movingObjs.size(); i++)
		m_movingObjs[i]->resetPos();
}
//-----------------------------------------------------------------------------
sf::Vector2f Board::getPlayerPos() const
{
	return m_movingObjs[0]->getPosition();
}
//-----------------------------------------------------------------------------
/*
Here we check whether amy of the enemies have caught our player which means 
the player is dead therefore loses a life or if an enemy is stuck in a hole
that the player dug
*/
bool Board::checkEnemyCollisions() const {
	for (int i = 1; i < m_movingObjs.size(); i++) {
		if (!inWindow(m_movingObjs[i]->getPosition()))
			continue;
		auto index = getIndexAtPos(m_movingObjs[i]->getPosition());
		if (Wall* p = dynamic_cast<Wall*>(m_staticObjs[index.y][index.x].get())) {
			auto wallPos = p->getPosition();
			if (wallPos.y <= m_movingObjs[i]->getPosition().y+5) {
				m_movingObjs[i]->setPosition({ wallPos.x, wallPos.y});
				p->fill();
				continue;
			}
		}
		if (m_movingObjs[i]->collide(m_movingObjs[0]->getGlobalBounds()))
		{
			Music::instance().playEnemy();
			return true;
		}
	}
	return false;
}
//-----------------------------------------------------------------------------
char Board::getCharAtLocation(sf::Vector2f pos) const {
	if (inWindow(pos)){
		auto index = getIndexAtPos(pos);
		auto ch = m_level->getChar(index.y, index.x);
		if (Wall* p = dynamic_cast<Wall*>(m_staticObjs[index.y][index.x].get()))
			if (!p->isEmpty())
				return WALL;
		return (ch != EMPTY && ch != PLAYER && ch != ENEMY && !m_staticObjs[index.y][index.x]->isRemoved()) ? ch : EMPTY;
	}
}

//-----------------------------------------------------------------------------
sf::Vector2f Board::getObjLocation(sf::Vector2f pos) const
{
	if (inWindow(pos)) {
		auto index = getIndexAtPos(pos);
		sf::Vector2f obj = getCoordinates(index.y, index.x);
		return (m_staticObjs[index.y][index.x]) ? m_staticObjs[index.y][index.x]->getPosition() : obj;
	}
	return pos;
}
//-----------------------------------------------------------------------------
sf::Vector2i Board::getIndexAtPos(sf::Vector2f pos) const {
	return { (int)(pos.x / m_cellSize.x), (int)(pos.y / m_cellSize.y)};
}
//-----------------------------------------------------------------------------
sf::Vector2i Board::getLevelSize() const
{
	return m_level->getMapSize();
}
//-----------------------------------------------------------------------------
sf::Vector2f Board::getCoordinates(int row, int col) const
{
	return { (m_cellSize.x / 2) - 1 + m_cellSize.x * col, (m_cellSize.y / 2) - 1 + m_cellSize.y * row };
}
//-----------------------------------------------------------------------------
void Board::dig(sf::Vector2f pos) const {
	
	auto index = getIndexAtPos(pos);
	if (inWindow(pos)) {
		if(m_level->getChar(index.y-1, index.x)!=WALL)
			if(Wall* p = dynamic_cast<Wall*>(m_staticObjs[index.y][index.x].get()))
				if(!p->isRemoved())
					p->toggleRemove();
	}
}
//-----------------------------------------------------------------------------
int Board::getCoinAmount() const
{
	return m_numOfCoins;
}
//-----------------------------------------------------------------------------
void Board::addEnemy()
{
	for (int i = 0 ; i < m_staticObjs.size(); i++)
		for (int j = 0; j < m_staticObjs[i].size(); j++)
			if (!m_staticObjs[i][j] && dynamic_cast<Wall*>(m_staticObjs[i+1][j].get())) {
				sf::Vector2f pos = getCoordinates(i, j);
				m_movingObjs.push_back(std::unique_ptr<BaseEnemy>(raffleEnemy(pos)));
				return;
			}
}
//-----------------------------------------------------------------------------
BaseEnemy* Board::raffleEnemy(sf::Vector2f pos) const {
	switch (rand() % 3) {
	case 0:
		return new StupidEnemy(pos, m_cellSize);
	case 1:
		return new PatrolEnemy(pos, m_cellSize);
	case 2:
		return new SmartEnemy(pos, m_cellSize);

	}
	return nullptr;
}
//-----------------------------------------------------------------------------
Bonus* Board::raffleBonus(sf::Vector2f pos) const {
	auto modo = (m_level->getTime() == -1) ? 3 : 4;
	switch (rand() % modo) {
	case 0:
		return new LifeBonus(pos, m_cellSize);
	case 1:
		return new PointBonus(pos, m_cellSize);
	case 2:
		return new EnemyBonus(pos, m_cellSize);
	case 3:
		return new TimeBonus(pos, m_cellSize);
	}
	return nullptr;
}
//-----------------------------------------------------------------------------
void Board::move(float dt)
{
	for (int j = 0; j < m_movingObjs.size(); j++) {
		m_movingObjs[j]->move(*this, dt);
		m_movingObjs[j]->changeAnimation(dt);
	}

	for (int i = 0; i < m_staticObjs.size(); i++)
		for (int j = 0; j < m_staticObjs[i].size(); j++)
			if (Wall* p = dynamic_cast<Wall*>(m_staticObjs[i][j].get()))
				if (p->checkTimer(dt))
					wallReturned(p);
}
//-----------------------------------------------------------------------------
/*
checks if the player collected an object
*/
void Board::collectObj(Controller& control) {
	auto index = getIndexAtPos(m_movingObjs[0]->getPosition());
	if (m_staticObjs[index.y][index.x]) {
		if (!m_staticObjs[index.y][index.x]->isRemoved()) {
			if (Coin * p = dynamic_cast<Coin*>(m_staticObjs[index.y][index.x].get()))
				p->collect(control);
			else if (Bonus* p = dynamic_cast<Bonus*>(m_staticObjs[index.y][index.x].get())) 
				p->collect(control);
		}
	}
}
//-----------------------------------------------------------------------------
/*
boolean function that returns true if the object at the input postion is a hole 
*/
bool Board::hole(sf::Vector2f pos) const
{
	auto index = getIndexAtPos(pos);
	if (Wall* p = dynamic_cast<Wall*>(m_staticObjs[index.y][index.x].get()))
		return p->isRemoved();
	return false;
}






