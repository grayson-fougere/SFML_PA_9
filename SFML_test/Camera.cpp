#include "Camera.hpp"

Camera::Camera() : staticTarget(), playerTarget(), sf::View() {
	setStaticTarget(getCenter());
}
Camera::Camera(sf::RenderWindow &window) : staticTarget(), playerTarget(), sf::View(sf::FloatRect({ 0.f, 0.f }, sf::Vector2f( window.getSize().x, window.getSize().y ))) {
	setStaticTarget(getCenter());
}
Camera::Camera(float width, float height, float x, float y) : staticTarget(), playerTarget(), sf::View(sf::FloatRect({ 0, 0 }, { width, height })) {
	setCenter({ x,y });
	setStaticTarget(getCenter());
}
Camera::Camera(sf::FloatRect windowRect) : staticTarget(), playerTarget(), sf::View(windowRect) {
	setStaticTarget(getCenter());
}

void Camera::changeDimensions(float width, float height) {
	setSize({ width, height });
	setCenter(getTargetPos());
}
void Camera::changeDimensions(sf::Vector2f dims) {
	setSize(dims);
	setCenter(getTargetPos());
}

void Camera::setDynamicTarget(PlayerBall &player) {
	playerTarget = &player;
	targetType = PLAYER;
}
void Camera::setStaticTarget(sf::Vector2f pos) {
	staticTarget = pos;
	targetType = STATIC;
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

void Camera::update() {
	setCenter(getTargetPos());
}