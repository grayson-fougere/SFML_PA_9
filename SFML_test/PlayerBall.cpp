#include "PlayerBall.hpp"

PlayerBall::PlayerBall(int radius, float speed) : momentum(sf::Vector2f()), moveSpeed(speed), sf::CircleShape(radius) {
	ballTexture = sf::Texture(sf::Image("Resources/Ball100.png")), sf::IntRect({ 0, 0 }, { 100, 100 });

	setTexture(&ballTexture);
}

void PlayerBall::update(int32_t dt) {
	// update momentum
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) momentum.x -= moveSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) momentum.x += moveSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) momentum.y -= moveSpeed * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) momentum.y += moveSpeed * dt;

	// apply movement
	move(momentum);
}

void PlayerBall::collide(std::vector<sf::FloatRect> collisionsToCheck) {
	// loop through all transforms to check
	for (auto rect : collisionsToCheck) {
		// check for collision
		if (getGlobalBounds().findIntersection(rect)) {
			// get centers of player and rect to avoid many func calls
			sf::Vector2f playerCenter = getGeometricCenter(),
				rectCenter = rect.getCenter();

			// if rect on left of player, move player to right edge of rect and stop horiz motion
			if (rectCenter.x < playerCenter.x && momentum.x < 0) {
				setPosition(sf::Vector2f(rect.position.x + rect.size.x, getPosition().y));
				momentum.x = 0;
			}
			// if player on left of rect, move player to left edge of rect and stop horiz motion
			if (playerCenter.x < rectCenter.x && momentum.x > 0) {
				setPosition(sf::Vector2f(rect.position.x - (getRadius() * 2), getPosition().y));
				momentum.x = 0;
			}
			// if rect above player, move player to bottom of rect and stop vert motion
			if (rectCenter.y < playerCenter.y && momentum.y < 0) {
				setPosition(sf::Vector2f(getPosition().x, rect.position.y + rect.size.y));
				momentum.y = 0;
			}
			// if player above below, move player to top of rect and stop vert motion
			if (playerCenter.y < rectCenter.y && momentum.y > 0) {
				setPosition(sf::Vector2f(getPosition().x, rect.position.y - (getRadius() * 2)));
				momentum.y = 0;
			}
			
		}
	}
}