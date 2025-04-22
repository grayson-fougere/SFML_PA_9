#include "coin.hpp"

// Constructor: Initialize sprite with texture, then set position and scale
Coin::Coin(const sf::Texture& texture, float x, float y)
    : sprite(texture)  // initialize sprite with texture
{
    sprite.setPosition(sf::Vector2f(300.0f, 300.0f));         // Set position
    sprite.setScale(sf::Vector2f(2.0f, 2.0f));      // Scale it up
}

void Coin::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

const sf::Sprite& Coin::getSprite() const {
    return sprite;
}