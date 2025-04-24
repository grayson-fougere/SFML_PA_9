#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Camera.hpp"

class Background {
public:
    Background();
    void draw(sf::RenderWindow& window, Camera& viewCam);
    void resize(sf::Vector2u windowSize);
    void scroll(float offset);

    sf::Texture bg_img;

private:
    std::vector<sf::Sprite*> images;
};
