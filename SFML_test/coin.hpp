#pragma once
#include <SFML/Graphics.hpp>

class Coin {
public:
    
    Coin(const sf::Texture& texture, const sf::Vector2f& position);

    void draw(sf::RenderWindow& window) const;
    const sf::Sprite& getSprite() const;

private:
    sf::Sprite sprite;  // No default construction allowed
};
