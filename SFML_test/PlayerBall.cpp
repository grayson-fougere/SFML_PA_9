#include "PlayerBall.hpp"

PlayerBall::PlayerBall(float radius) : PlayerBall(radius, 0, 0, 0, { 0, 0 }) {}

PlayerBall::PlayerBall(float radius, float accel, float jump, float gravity, sf::Vector2f moveSpeedCap)
		: _accel(accel), _jump(jump), _gravity(gravity), _moveSpeedCap(moveSpeedCap), sf::CircleShape(radius) {

	_ballTexture = sf::Texture(sf::Image("Resources/Ball100.png")), sf::IntRect({ 0, 0 }, { 100, 100 });

	setTexture(&_ballTexture);
}

void PlayerBall::setAccel(float newAccel) { _accel = newAccel; }
void PlayerBall::setMoveSpeedCap(sf::Vector2f newCap) { _moveSpeedCap = newCap; }
void PlayerBall::setGravity(float newGravity) { _gravity = newGravity; }

void PlayerBall::update(int32_t dt) {
	// update momentum
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) _momentum.x -= _accel * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) _momentum.x += _accel * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) _momentum.y -= _jump;
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) _momentum.y += _accel * dt;

	// add gravity
	_momentum.y += _gravity * dt;

	// apply movement
	move(_momentum);
}

void PlayerBall::collide(std::vector<sf::FloatRect> collisionsToCheck) {
	//// loop through all transforms to check
	//for (auto rect : collisionsToCheck) {
	//	// check for collision
		//if (getGlobalBounds().findIntersection(rect)) {
	//		// get centers of player and rect to avoid many func calls
	//		sf::Vector2f playerCenter = getGeometricCenter(),
	//			rectCenter = rect.getCenter();

	//		// if rect on left of player, move player to right edge of rect and stop horiz motion
	//		if (rectCenter.x < playerCenter.x && momentum.x < 0) {
	//			setPosition(sf::Vector2f(rect.position.x + rect.size.x, getPosition().y));
	//			momentum.x = 0;
	//		}
	//		// if player on left of rect, move player to left edge of rect and stop horiz motion
	//		if (playerCenter.x < rectCenter.x && momentum.x > 0) {
	//			setPosition(sf::Vector2f(rect.position.x - (getRadius() * 2), getPosition().y));
	//			momentum.x = 0;
	//		}
	//		// if rect above player, move player to bottom of rect and stop vert motion
	//		if (rectCenter.y < playerCenter.y && momentum.y < 0) {
	//			setPosition(sf::Vector2f(getPosition().x, rect.position.y + rect.size.y));
	//			momentum.y = 0;
	//		}
	//		// if player above below, move player to top of rect and stop vert motion
	//		if (playerCenter.y < rectCenter.y && momentum.y > 0) {
	//			setPosition(sf::Vector2f(getPosition().x, rect.position.y - (getRadius() * 2)));
	//			momentum.y = 0;
	//		}
	//		
	//	}
	//}
}

void PlayerBall::collideTop(sf::RectangleShape floor) {
	if (getGlobalBounds().findIntersection(floor.getGlobalBounds())) {
	    //shape.setPosition({get})
	    sf::Vector2f playerCurPos = getPosition();
	    sf::Vector2f objCurPos = floor.getPosition();
	    sf::Vector2f offset({ 0.f, -200.1f });
	    setPosition({ playerCurPos.x, objCurPos.y + offset.y });
	    _momentum.y = (0.f);
	}
	//else if (!getGlobalBounds().findIntersection(floor.getGlobalBounds()) && _momentum.y < (35.f)) {
	//    _momentum.y += _gravity;
	//}
}

void PlayerBall::collideView(sf::Vector2u windowSize) {
	// left of window
	float newX = getPosition().x,
		newY = getPosition().y,
		newXMom = _momentum.x,
		newYMom = _momentum.y;

	// left of window
	if (newX < 0) {
		newX = 0;
		newXMom = 0;
	}
	// right of window
	if (newX + (getRadius() * 2) > windowSize.x) {
		newX = windowSize.x - (getRadius() * 2);
		newXMom = 0;
	}

	// above window
	if (newY < 0) {
		newY = 0;
		newYMom = 0;
	}

	// below window
	if (newY + (getRadius() * 2) > windowSize.y) {
		newY = windowSize.y - (getRadius() * 2);
		newYMom = 0;
	}

	setPosition({ newX, newY });
	_momentum = { newXMom, newYMom };
}