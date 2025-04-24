#include "Background.hpp"
#include <iostream>


Background::Background() {
    // load image
    bg_img.loadFromFile("Textures/background.png");

    // add textures to vector
    for (float i = -10; i < 20; i++) {
        sf::Sprite* newSprite = new sf::Sprite(bg_img);
        newSprite->setPosition(sf::Vector2f(i * bg_img.getSize().x, 0.f));
        std::cout << newSprite->getPosition().x << std::endl;
        images.push_back(newSprite);
    }
}

void Background::draw(sf::RenderWindow& window, Camera& viewCam) {
    for (auto*& sprite : images) {
        sprite->setPosition({ sprite->getPosition().x, viewCam.getTopY()});
        window.draw(*sprite);
    }
}
void Background::resize(sf::Vector2u windowSize) {
    for (auto& layer : images) {
        const auto texSize = layer->getTexture().getSize();
        if (texSize.x == 0 || texSize.y == 0) continue;

        layer->setScale({
            static_cast<float>(windowSize.x) / texSize.x,
            static_cast<float>(windowSize.y) / texSize.y
            });
    }
}
void Background::scroll(float offset) {
    for (auto*& sprite : images) {
        sprite->move({ offset, 0 });
    }
}
void Background::clear() {
    for (auto*& sprite : images) {
        delete sprite;
    }
    images.clear();
}