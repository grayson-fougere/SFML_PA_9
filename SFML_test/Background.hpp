#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
class Background {
public:
    Background();
    void draw(sf::RenderWindow& window);
    void resize(sf::Vector2u windowSize);
    void scroll(float offset);

    sf::Texture farTex, midTex, nearTex;

private:
    struct Layer {
        Layer(sf::Texture& tex, float speed);
        sf::Texture& texture;
        sf::Sprite sprite;
        float scrollSpeed;
    };

    std::vector<Layer> layers;
};
