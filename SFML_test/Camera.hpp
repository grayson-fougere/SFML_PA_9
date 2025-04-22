#include <SFML/Graphics.hpp>
#include "PlayerBall.hpp"

class Camera : public sf::View {

public:
	/* ----- Constructors ----- */

	// blank Camera constructor, with default sf::View and default top left of {0.f, 0.f}
	Camera();
	// Camera constructor given window. Sets view of window size and top left pos of {0.f, 0.f}
	Camera(sf::RenderWindow& window);
	// Camera constructor given window and player to follow. Sets view of window size and dynamically follow player
	Camera(sf::RenderWindow& window, PlayerBall& playerToFollow);

	/* ----- Setters ----- */

	// Update the view size to match the given window
	void updateWindow(sf::RenderWindow& window);
	// Update which player object to follow. Does NOT change to dynamic following.
	void updatePlayer(PlayerBall& newPlayerToFollow);
	// Update which center position to follow. Does NOT change to static following.
	void updateStaticCenter(sf::Vector2f newPos);
	// Update which center position to follow, given top-left pos. Does NOT change to static following.
	void updateStaticPos(sf::Vector2f newPos);

	/* ----- Getters ----- */
	// Get the center pos to follow. Based on static vector or player's current pos
	sf::Vector2f getTargetPos();

	/* ----- Toggles ----- */
	// Changes following to dynamic (player)
	void followPlayer();
	// Changes following to static (vector)
	void followStatic();

	// Mainloop function to call. Updates position.
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
