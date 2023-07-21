#include "..\include\SmartEnemy.h"
#include "Board.h"
#include <iostream>
SmartEnemy::SmartEnemy(sf::Vector2f pos, sf::Vector2f size) :
	BaseEnemy(pos, size)
{
	m_speed = 180.f;
}
//-----------------------------------------------------------------------------

void SmartEnemy::move(const Board& board, float dt) {
	auto playerPos = board.getPlayerPos();
	auto pos = getPosition();
	auto speed = m_speed * dt;
	auto checkVirtical = true, foundL = true, foundR = true, checkObs = false;
	auto options = getMoveOptions(speed);
	Direction obsDirecY = stop, direcY;

	if (checkIfFalling(board, speed)) {
		m_direction = down;
		if (isValidMove(board, options[down], speed))
			m_sprite.setPosition(options[down]);
		return;
	}
	sf::Vector2f verticalP = pos, leftP, rightP, obsticalP;
	auto verticalDirc = stop;
	if (playerPos.y > pos.y) //going down
		direcY = down;
	else if (playerPos.y <= pos.y) 
		direcY = up;

	leftP = findWay(pos, board, left, direcY, playerPos, foundL);
	rightP = findWay(pos, board, right, direcY, playerPos, foundR);
	m_direction = direcY;
	if (isValidMove(board, options[direcY], speed)) {
		verticalP = findCoordAtEnd(pos, direcY, board, playerPos);
		verticalDirc = direcY;
	}

	if (verticalDirc == stop)
		checkVirtical = false;
	if (!foundL && !foundR)
		obsticalP = obsticalOvercome(pos, playerPos, board, checkObs, obsDirecY);

	auto dir = getMinDistence(playerPos, leftP, rightP, verticalP, checkVirtical, foundL, foundR, checkObs, obsticalP);
	if (dir == left) {
		if (tryMove(left, options[left], board, speed))
			return;
	}
	else if (dir == right) {
		if (tryMove(right, options[right], board, speed))
			return;
	}
	else if (dir == up) {
		if (tryMove(obsDirecY, options[obsDirecY], board, speed))
			return;
	}
	m_direction = verticalDirc;
	if (m_direction != stop)
		m_sprite.setPosition(options[verticalDirc]);
	return;
}

//-----------------------------------------------------------------------------
//checks if a desired move is valid
bool SmartEnemy::tryMove(Direction direc, sf::Vector2f& pos, const Board& board, float speed) {
	m_direction = direc;
	if (isValidMove(board, pos, speed)) {
		m_sprite.setPosition(pos);
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
//check for a way up/down in the desired direction
//and returns the location at the end of the way up or down
sf::Vector2f SmartEnemy::findWay(sf::Vector2f pos, const Board& board, Direction direcX, Direction direcY, sf::Vector2f player, bool& found) {

	auto newPos = pos;
	auto size = getSize();
	auto pInd = board.getIndexAtPos(player);
	auto ind = board.getIndexAtPos(pos);
	newPos = { board.getObjLocation(pos).x, newPos.y + getReach().y-1 };
	auto signX = (direcX == left) ? LEFT : RIGHT;
	auto signY = (direcY == up) ? 0 : 1;
	char ch; float i;
	for (i = newPos.x + signX * size.x; board.inWindow({ i,newPos.y }); i += signX * size.x) {
		ch = board.getCharAtLocation({ i,newPos.y });
		if (ch == WALL) {
			found = false;
			return { i ,pos.y };
		}
		if (pInd.y == ind.y && abs(i - player.x) < size.x / 2)
			return { i,pos.y };
		ch = board.getCharAtLocation({ i,newPos.y + signY * size.y });
		if (pInd.y != ind.y && (ch == LADDER || (direcY == down && ch == EMPTY && !board.hole({ i,newPos.y + signY * size.y }))))
			return findCoordAtEnd({ i,newPos.y - getReach().y }, direcY, board, player);
	}
	found = false;
	return { i - signX * size.x,newPos.y };
}

//-----------------------------------------------------------------------------
//goes up or down until can't anymore and returns coordinates reached
sf::Vector2f SmartEnemy::findCoordAtEnd(sf::Vector2f pos, Direction direc, const Board& board, sf::Vector2f player) {
	auto sign = (direc == up) ? LEFT : RIGHT;
	char ch;
	auto size = getSize();
	for (float i = pos.y; board.inWindow({ pos.x, i }); i += sign * size.y) {
		ch = board.getCharAtLocation({ pos.x,i });
		if (direc == up && ch == LADDER)
			continue;
		if (ch == WALL)
			return { pos.x, i - sign * size.y };
		if ((direc == up && ch != WALL) || (i != pos.y && ch == RAIL))
			return { pos.x, i };
		if (direc == up && i < player.y || direc == down && i > player.y)
			return { pos.x, i };
	}
}

//-----------------------------------------------------------------------------
//returns the direction to go to towards the point reached that is closest to
//the player, takes into account if a path was found or not
Direction SmartEnemy::getMinDistence(sf::Vector2f playerPos, sf::Vector2f goLeft, sf::Vector2f goRight,
	sf::Vector2f vertical, bool checkVirtical, bool foundL, bool foundR, bool checkObs, sf::Vector2f obs) {
	float verticalDis = 2000;
	float obsDis = 2000;
	auto leftDis = std::hypot(goLeft.x - playerPos.x, goLeft.y - playerPos.y);
	auto rightDis = std::hypot(goRight.x - playerPos.x, goRight.y - playerPos.y);
	if (checkVirtical)
		verticalDis = std::hypot(vertical.x - playerPos.x, vertical.y - playerPos.y);
	if (checkObs)
		obsDis = std::hypot(obs.x - playerPos.x, vertical.y - playerPos.y);

	if ((leftDis > rightDis || !foundL) && verticalDis > rightDis && foundR && obsDis > rightDis)
		return right;
	if ((rightDis > leftDis || !foundR) && verticalDis > leftDis && foundL && obsDis > leftDis)
		return left;
	if (checkObs && (leftDis > obsDis || !foundL) && (rightDis > obsDis || !foundR) && verticalDis >= obsDis)
		return up;
	return stop;
}

//-----------------------------------------------------------------------------
//in cases where there is an obsitcal tries to find a way around and returns the 
//position after the overcome
sf::Vector2f SmartEnemy::obsticalOvercome(sf::Vector2f pos, sf::Vector2f playerPos, const Board& board, bool& found, Direction& dirc) {
	pos = { pos.x, pos.y + getReach().y };
	auto pInd = board.getIndexAtPos(playerPos);
	auto ind = board.getIndexAtPos(pos);
	auto dircX = (playerPos.x > pos.x) ? RIGHT : LEFT;
	auto dircY = (pInd.y > ind.y) ? RIGHT : LEFT;
	auto size = getSize();
	for (float i = pos.y + dircY * size.y; board.inWindow({ pos.x, i }); i += dircY * size.y) {
		if (board.getCharAtLocation({ pos.x,i }) != LADDER)
			break;
		if (board.getCharAtLocation({ pos.x + dircX * size.x,i }) == WALL)
			continue;
		else {
			found = true;
			dirc = (dircY > 0) ? down : up;
			return { pos.x + dircX * size.x,i };
		}
	}
	found = false;
	return pos;
}