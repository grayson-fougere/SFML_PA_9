#pragma once
#include <SFML/Graphics.hpp>
#include "Collidable.hpp"

class Enemy : public sf::RectangleShape, public Collidable {
public:
	Enemy(const sf::Vector2f& newStartPos = { 0,0 }, const sf::Vector2f& newEndPos = {0,1}, const float& newSpeed=0.1);
	void onCollide(Collidable* obj, std::vector<sf::Vector2f> points) override;

	sf::Vector2f getStartPos();
	sf::Vector2f getEndPos();
	//float getMoveSpeed(); I dont think we need this

	void setStartPos(const sf::Vector2f& newStartPos);
	void setEndPos(const sf::Vector2f& newEndPos);
	void setMoveSpeed(const float& newSpeed);
private:
	sf::Vector2f startPos, endPos;
	float moveSpeed;
};