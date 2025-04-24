#pragma once
#include "Collidable.hpp"

class Platform : public sf::RectangleShape, public Collidable {
public:
	Platform(sf::Vector2f pos, float width, float height, sf::Color fill = sf::Color::Green);
	Platform(sf::Vector2f pos, sf::Vector2f scale, sf::Color fill = sf::Color::Green);
};