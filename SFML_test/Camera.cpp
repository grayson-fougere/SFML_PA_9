#include "Camera.hpp"

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

sf::Vector2f Camera::getTargetPos() {
	switch (targetType) {
	case PLAYER:
		if (playerTarget != nullptr) return playerTarget->getPosition();
		return staticTarget;
	case STATIC:
		return staticTarget;
	}

	return sf::Vector2f();
}

void Camera::followPlayer() {
	targetType = PLAYER;
}
void Camera::followStatic() {
	targetType = STATIC;
}

void Camera::update() {
	setCenter(getTargetPos());
}