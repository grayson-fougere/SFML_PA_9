#include "Enemy.hpp"

Enemy::Enemy(const sf::Vector2f& newStartPos, const sf::Vector2f& newEndPos, const float& newSpeed) : Collidable("Enemy")
{
	// oooh the misery
	startPos = newStartPos;
	endPos = newEndPos;
	moveSpeed = newSpeed;
}

void Enemy::onCollide(Collidable* obj, std::vector<sf::Vector2f> points)
{

}

sf::Vector2f Enemy::getStartPos()
{
	return this->startPos;
}

sf::Vector2f Enemy::getEndPos()
{
	return this->endPos;
}

void Enemy::setStartPos(const sf::Vector2f& newStartPos)
{
	this->startPos = newStartPos;
}

void Enemy::setEndPos(const sf::Vector2f& newEndPos)
{
	this->endPos = newEndPos;
}

void Enemy::setMoveSpeed(const float& newSpeed)
{
	this->moveSpeed = newSpeed;
}
