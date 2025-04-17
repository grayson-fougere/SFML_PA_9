#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class PlayerBall : public sf::CircleShape {

public:
	PlayerBall(float radius);
	PlayerBall(float radius, float accel, float jump, float gravity, sf::Vector2f moveSpeedCap);

	// setters
	void setAccel(float newAccel);
	void setMoveSpeedCap(sf::Vector2f newCap);
	void setGravity(float newGravity);
	void setHasJumped(bool newJumpStatus);

	void update(int32_t dt);
	void collide(std::vector<sf::FloatRect> collisionsToCheck);
	void collideObstacles(std::vector<sf::ConvexShape> obstacles);
	void collideTop(sf::RectangleShape floor);
	void collideView(sf::Vector2u windowSize);

private:
	sf::Vector2f _momentum;
	float _gravity;
	float _accel;
	float _jump;
	bool hasJumped;
	sf::Vector2f _moveSpeedCap;
	sf::Texture _ballTexture;
};