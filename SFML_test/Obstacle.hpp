#include <SFML/Graphics.hpp>

class Obstacle : public sf::RectangleShape {

public:
	Obstacle(float width, float height);
	Obstacle(sf::Vector2f size = { 0.0, 0.0 }, sf::Vector2f position = { 0.0, 0.0 });

private:
	sf::Texture obstTexture;
};