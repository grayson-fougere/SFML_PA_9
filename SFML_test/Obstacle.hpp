#include <SFML/Graphics.hpp>
#include "Collidable.hpp"

class Obstacle : public sf::RectangleShape, public Collidable {

public:
	Obstacle(float width, float height);
	Obstacle(sf::Vector2f size = { 0.0, 0.0 }, sf::Vector2f position = { 0.0, 0.0 });
	void onCollide(Collidable* obj) override;
private:
	sf::Texture obstTexture;
};