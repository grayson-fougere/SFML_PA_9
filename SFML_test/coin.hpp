#pragma once
#include <SFML/Graphics.hpp>

class Coin {
public:
	Coin(const sf::Texture& texture, float x, float y);

    // draw the coin to the window
    void draw(sf::RenderWindow& window);

    // get a reference to the internal sprite (e.g., for positioning)
    const sf::Sprite& getSprite() const;
private:
	sf::Sprite sprite;
};