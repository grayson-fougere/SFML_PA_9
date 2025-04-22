#pragma once
#include <SFML/Graphics.hpp>
#include "Collidable.hpp"

class Spike: public sf::ConvexShape, public Collidable {
public:
	Spike(sf::Vector2f position = { 0, 0 }, float scale = 1, sf::Color fillColor = sf::Color::Black);
};