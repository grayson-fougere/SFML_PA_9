#include "coin.hpp"

// Constructor
Coin::Coin(const sf::Texture& texture, const sf::Vector2f& position)
    : sprite(texture)  // Initialize sprite with texture here
{
    // then set other properties
    sprite.setPosition(position);
    sprite.setScale(sf::Vector2f(0.3f, 0.3f));
}

void Coin::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

const sf::Sprite& Coin::getSprite() const {
    return sprite;
}