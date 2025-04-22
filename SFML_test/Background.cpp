#include "Background.hpp"
#include <iostream>

// updated constructor: pass texture by reference
Background::Layer::Layer(sf::Texture& tex, float speed)
    : texture(tex), sprite(tex), scrollSpeed(speed) {
    // sprite is safely initialized with a valid reference
}

Background::Background() {
    try {
        // load textures
        if (!farTex.loadFromFile("Textures/space_far.jpg")) {
            std::cerr << "Failed to load far layer texture\n";
        }
        if (!midTex.loadFromFile("Textures/space_mid.jpg")) {
            std::cerr << "Failed to load mid layer texture\n";
        }
        if (!nearTex.loadFromFile("Textures/space_near.jpg")) {
            std::cerr << "Failed to load near layer texture\n";
        }

        // construct layers with valid texture references (no move)
        layers.emplace_back(farTex, 0.2f);
        layers.emplace_back(midTex, 0.5f);
        layers.emplace_back(nearTex, 0.8f);
    }
    catch (const std::exception& e) {
        std::cerr << "Background initialization error: " << e.what() << "\n";
    }
}

void Background::draw(sf::RenderWindow& window) {
    for (auto& layer : layers) {
        window.draw(layer.sprite);
    }
}

void Background::resize(sf::Vector2u windowSize) {
    for (auto& layer : layers) {
        const auto texSize = layer.texture.getSize();
        if (texSize.x == 0 || texSize.y == 0) continue;

        layer.sprite.setScale({
            static_cast<float>(windowSize.x) / texSize.x,
            static_cast<float>(windowSize.y) / texSize.y
            });
    }
}

void Background::scroll(float offset) {
    for (auto& layer : layers) {
        float layerOffset = offset * layer.scrollSpeed;
        auto position = layer.sprite.getPosition();
        position.x += layerOffset;

        const float scaledWidth = layer.texture.getSize().x * layer.sprite.getScale().x;

        if (position.x <= -scaledWidth) {
            position.x += scaledWidth;
        }
        else if (position.x >= scaledWidth) {
            position.x -= scaledWidth;
        }

        layer.sprite.setPosition(position);
    }
}
