#include <SFML/Graphics.hpp>
#include "PlayerBall.hpp"

class Camera : public sf::View {

public:
	Camera();
	Camera(sf::RenderWindow &window);
	Camera(float width, float height, float x, float y);
	Camera(sf::FloatRect windowRect);

	void changeDimensions(float width, float height);
	void changeDimensions(sf::Vector2f dims);

	void setDynamicTarget(PlayerBall &player);
	void setStaticTarget(sf::Vector2f pos);

	sf::Vector2f getTargetPos();

	void update();

private:
	sf::Vector2f staticTarget;
	PlayerBall *playerTarget;

	enum TargetType {
		STATIC,
		PLAYER
	};

	TargetType targetType;
};
