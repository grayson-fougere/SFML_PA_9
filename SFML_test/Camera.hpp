#include <SFML/Graphics.hpp>
#include "PlayerBall.hpp"

class Camera : public sf::View {

public:
	Camera();
	Camera(sf::RenderWindow& window);
	Camera(sf::RenderWindow& window, PlayerBall& playerToFollow);

	// setters
	void updateWindow(sf::RenderWindow& window);
	void updatePlayer(PlayerBall& newPlayerToFollow);
	void updateStaticCenter(sf::Vector2f newPos);
	void updateStaticPos(sf::Vector2f newPos);

	// getters
	sf::Vector2f getTargetPos();

	// toggles
	void followPlayer();
	void followStatic();

	// mainloop update func
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
