#include <SFML/Graphics.hpp>
#include "PlayerBall.hpp"

// TODO: WILL NEED TO ADD CLAMPING AND LOCKS TO X AND Y POS
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
	// Set offset from view (top right) to place coin sprite {right of screen - X, top of screen + Y}
	void setCoinSpriteOffset(sf::Vector2f newOffset);
	// Set offset from view (top right) to place coin counter {right of screen - X, top of screen + Y}
	void setCoinCounterOffset(sf::Vector2f newOffset);

	/* ----- Getters ----- */
	// Get the center pos to follow. Based on static vector or player's current pos
	sf::Vector2f getTargetPos();
	// Get global position to draw coin sprite
	sf::Vector2f getCoinSpritePos();
	// Get global position to draw coin counter
	sf::Vector2f getCoinCounterPos();

	/* ----- Toggles ----- */
	// Changes following to dynamic (player)
	void followPlayer();
	// Changes following to static (vector)
	void followStatic();

	/* ----- MainLoop Functions ----- */
	void update();

private:
	// Offset for coin sprite on screen
 	sf::Vector2f coinSpriteOffset;
	// Offset for coin counter text on screen
	sf::Vector2f coinCounterOffset;

	
	// targets
	sf::Vector2f staticTarget;
	PlayerBall *playerTarget;

	enum TargetType {
		STATIC,
		PLAYER
	};

	TargetType targetType;
};
