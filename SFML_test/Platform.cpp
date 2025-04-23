#include "Platform.hpp"

// Collidable already has most libraries lmao
Platform::Platform(sf::Vector2f pos, float width, float height, sf::Color fill) : RectangleShape({width, height}), Collidable("Floor") {
	setPosition(pos);
	setFillColor(fill);
}