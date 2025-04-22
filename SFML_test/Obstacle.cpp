#include "Obstacle.hpp"

Obstacle::Obstacle(float width, float height) : sf::RectangleShape({ width, height }), Collidable("Obstacle") {
	setFillColor(sf::Color::Red);
	setPosition({ 50, 50 });
}

Obstacle::Obstacle(sf::Vector2f size, sf::Vector2f position)
	: sf::RectangleShape(size), Collidable("Obstacle") {

	setFillColor(sf::Color::Red);
	setPosition(position);
}

void Obstacle::onCollide(Collidable* obj)
{
	if (obj->getTag() == "Player") {
		// kill player
	}
}
