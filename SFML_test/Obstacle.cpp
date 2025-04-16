#include "Obstacle.hpp"

Obstacle::Obstacle(float width, float height) : sf::RectangleShape({ width, height }) {
	setFillColor(sf::Color::Red);
	setPosition({ 50, 50 });
}

Obstacle::Obstacle(sf::Vector2f size, sf::Vector2f position)
	: sf::RectangleShape(size) {

	setFillColor(sf::Color::Red);
	setPosition(position);
}