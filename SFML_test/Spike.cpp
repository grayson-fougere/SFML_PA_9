#include "Spike.hpp"

Spike::Spike(sf::Vector2f position, float scale, sf::Color fillColor) : ConvexShape(3), Collidable("Obstacle") {
	setTexture(new sf::Texture("Textures/spike2.png"));
	setPoint(0, { 0.f, -10.f });
	setPoint(1, { 5.0f, 0.f });
	setPoint(2, { -5.0f, 0.f });
	setPosition(position);
	setScale(sf::Vector2(scale, scale));
	//setFillColor(fillColor);
}
