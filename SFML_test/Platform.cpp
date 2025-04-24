#include "Platform.hpp"

// Collidable already has most libraries lmao
Platform::Platform(sf::Vector2f pos, float width, float height, sf::Color fill) : RectangleShape({width, height}), Collidable("Floor") {
	sf::Texture* tex = new sf::Texture("Textures/grass.jpg");
	setTexture(tex);
	setPosition(pos);
	setFillColor(fill);
}