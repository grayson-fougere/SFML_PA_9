#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class PlayerBall : public sf::CircleShape {

public:
	PlayerBall(int radius, float speed);

	void update(int32_t dt);
	void collide(std::vector<sf::FloatRect> collisionsToCheck);

private:
	sf::Vector2f momentum;
	float moveSpeed;
	sf::Texture ballTexture;
};