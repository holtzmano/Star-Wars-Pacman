#pragma once
#include <GameObj.h>
#include <SFML/Graphics.hpp>
#include <Macros.h>
//-----------------------------------------------------------------------------

class Board;

class MovingObj : public GameObj
{
public:
	MovingObj(const sf::Texture* = nullptr, sf::Vector2f = { 0,0 }, sf::Vector2f = { 0,0 });
	virtual void draw(sf::RenderWindow& window) const;
	virtual void move(const Board&, float);
	virtual void resetPos();
	void changeAnimation(float dt);

protected:
	bool checkIfFalling(const Board&, float);
	Direction m_direction;
	bool isValidMove(const Board&, sf::Vector2f&, float speed);
	float m_speed = 180.f;

private:
	int m_animationCol = 0;
	float m_animationTimer = 0.2f;
	float m_nextAnimation = 0.2f;
	bool m_onLadder = false;
	sf::Vector2f m_startingPos;
	std::vector<char> getSurroundings(sf::Vector2f, const Board&, float) const;
};