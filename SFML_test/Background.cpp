#include "Background.hpp"
#include <iostream>

Background::Background() {
    if (!texture.loadFromFile("Textures/space.jpg")) {
        std::cerr << "ERROR: Failed to load background texture\n";
    }

    sprite_ptr = new sf::Sprite(texture);  // make new sprite instance from texture we got
}

void Background::draw(sf::RenderWindow& win) {
    win.draw(*sprite_ptr);  // dereference sprite and draw it
}
void Background::resize(sf::Vector2u windowSize) {
    sprite_ptr->setScale(sf::Vector2f(
        float(windowSize.x) / texture.getSize().x,
        float(windowSize.y) / texture.getSize().y
    ));
}
