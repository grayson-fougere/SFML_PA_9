#pragma once
#include <SFML/Graphics.hpp>

class Background {
public:
    Background();                      // constructor
    void draw(sf::RenderWindow& win); // draw function
    void resize(sf::Vector2u windowSize);
private:
    sf::Texture texture;
    sf::Sprite* sprite_ptr; // make for pointer to avoid trying to construct a sprite from a texture we don't have yet
};
