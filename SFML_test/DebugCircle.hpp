#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


// Circle that will have transparent fill, green outline, and be centered whenever setPosition is called
class DebugCircle : public sf::CircleShape {
public:
	DebugCircle(float radius, float thickness) : CircleShape(radius)  {
		setFillColor(sf::Color::Transparent);
		setOutlineColor(sf::Color::Green);
		setOutlineThickness(thickness);
	}
	void setPosition(sf::Vector2f newPosition) {
		((CircleShape*)(this))->setPosition(newPosition);
		this->move(sf::Vector2f(-1, -1)*getRadius());
	}
};