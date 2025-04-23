#include "Camera.hpp"

/* ----- Constructors ----- */

Camera::Camera() : staticTarget(), playerTarget(), sf::View() {
	updateStaticPos(sf::Vector2f());
	followStatic();
}
Camera::Camera(sf::RenderWindow& window) : staticTarget(), playerTarget(), sf::View() {
	updateWindow(window);
}
Camera::Camera(sf::RenderWindow& window, PlayerBall& playerToFollow) : staticTarget(), playerTarget(), sf::View() {
	updateWindow(window);
	updatePlayer(playerToFollow);
	followPlayer();
}

/* ----- Setters ----- */

void Camera::updateWindow(sf::RenderWindow& window) {
	setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
}
void Camera::updatePlayer(PlayerBall& newPlayerToFollow) {
	playerTarget = &newPlayerToFollow;
}
void Camera::updateStaticCenter(sf::Vector2f newPos) {
	staticTarget = newPos;
}
void Camera::updateStaticPos(sf::Vector2f newPos) {
	staticTarget = newPos + sf::Vector2f((getSize().x /2), (getSize().y /2));
}
void Camera::setCoinSpriteOffset(sf::Vector2f newOffset) {
	coinSpriteOffset = newOffset;
}
void Camera::setCoinCounterOffset(sf::Vector2f newOffset) {
	coinCounterOffset = newOffset;
}

/* ----- Getters ----- */

sf::Vector2f Camera::getTargetPos() {
	sf::Vector2f target;

	switch (targetType) {
	case PLAYER:
		if (playerTarget != nullptr) {
			// Only take the X position from player, keep existing Y
			target.x = playerTarget->getPosition().x;
			target.y = getCenter().y; // Keep current vertical position
		}
		else {
			target = staticTarget;
		}
		break;
	case STATIC:
		target = staticTarget;
		break;
	}

	return target;
}
sf::Vector2f Camera::getCoinSpritePos() {
	return sf::Vector2f(
		getCenter().x + (getSize().x / 2) - coinSpriteOffset.x,  // X: get center, move to right side, and subtract offset
		getCenter().y - (getSize().y /2) + coinSpriteOffset.y);  // Y: get center, move to top, and add offset
}
sf::Vector2f Camera::getCoinCounterPos() {
	return sf::Vector2f(
		getCenter().x + (getSize().x / 2) - coinCounterOffset.x,   // X: get center, move to right side, and subtract offset
		getCenter().y - (getSize().y / 2) + coinCounterOffset.y);  // Y: get center, move to top, and add offset
}

/* ----- Toggles ----- */

void Camera::followPlayer() {
	targetType = PLAYER;
}
void Camera::followStatic() {
	targetType = STATIC;
}

/* ----- MainLoop Functions ----- */

void Camera::update() {
	setCenter(getTargetPos());
}