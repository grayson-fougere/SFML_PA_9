#include "Camera.hpp"

/* ----- Constructors ----- */

Camera::Camera() : coinCounterOffset(), coinSpriteOffset(), playerTarget(), yPos(0), sf::View() {}
Camera::Camera(sf::RenderWindow& window) : coinCounterOffset(), coinSpriteOffset(), playerTarget(), yPos(0), sf::View() {
	updateWindow(window);
}
Camera::Camera(sf::RenderWindow& window, PlayerBall& playerToFollow) : Camera(window, playerToFollow, playerTarget->getPosition().y + playerToFollow.getRadius()) {}
Camera::Camera(sf::RenderWindow& window, PlayerBall& playerToFollow, float y_pos) : coinCounterOffset(), coinSpriteOffset(), playerTarget(&playerToFollow), yPos(y_pos), sf::View() {
	updateWindow(window);
}

/* ----- Setters ----- */

void Camera::updateWindow(sf::RenderWindow& window) {
	setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
}
void Camera::updatePlayer(PlayerBall& newPlayerToFollow) {
	playerTarget = &newPlayerToFollow;
}
void Camera::updateYPos(float newYPos) {
	yPos = newYPos;
}
void Camera::setCoinSpriteOffset(sf::Vector2f newOffset) {
	coinSpriteOffset = newOffset;
}
void Camera::setCoinCounterOffset(sf::Vector2f newOffset) {
	coinCounterOffset = newOffset;
}

/* ----- Getters ----- */

sf::Vector2f Camera::getTargetPos() {
	return sf::Vector2f(playerTarget->getPosition().x, yPos);
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

/* ----- MainLoop Functions ----- */

void Camera::update() {
	setCenter(getTargetPos());
}