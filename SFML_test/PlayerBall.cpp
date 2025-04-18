#include "PlayerBall.hpp"
#include "CollisionHelper.hpp"

PlayerBall::PlayerBall(float radius) : PlayerBall(radius, 0, 0, 0, {0, 0}) {}

PlayerBall::PlayerBall(float radius, float accel, float jump, float gravity, sf::Vector2f moveSpeedCap)
		: _accel(accel), _jump(jump), _gravity(gravity), _moveSpeedCap(moveSpeedCap), hasJumped(false), sf::CircleShape(radius), Collidable("Player") {

	_ballTexture = sf::Texture(sf::Image("Resources/Ball100.png"), true), sf::IntRect({ 0, 0 }, { 100, 100 });

	setTexture(&_ballTexture);
}

void PlayerBall::setAccel(float newAccel) { _accel = newAccel; }
void PlayerBall::setMoveSpeedCap(sf::Vector2f newCap) { _moveSpeedCap = newCap; }
void PlayerBall::setGravity(float newGravity) { _gravity = newGravity; }
void PlayerBall::setHasJumped(bool newJumpStatus) { hasJumped = newJumpStatus; }

void PlayerBall::update(int32_t dt) {
	// update momentum - step 0 [input]
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) _momentum.x -= _accel * dt;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) _momentum.x += _accel * dt;
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) &&
		!hasJumped) {

		_momentum.y -= _jump * dt;
		hasJumped = true;
	}

	// add gravity
	_momentum.y += _gravity * dt;

	// apply movement - step 1 of whiteboard
	move(_momentum);
}

void PlayerBall::collide(std::vector<sf::FloatRect> collisionsToCheck) {
	// loop through all rects to check
	for (auto rect : collisionsToCheck) {
		// step 2 - find intersecting rectangle, if any
		auto collRectOpt = getGlobalBounds().findIntersection(rect);

		// continue on with list if no collision
		if (!collRectOpt) continue;

		// BAD way to enable jump again
		if (_momentum.y > 0) hasJumped = false;

		// step 3 - find min length to move out of collision from
		auto collRect = collRectOpt.value();
		float collLen = collRect.size.x < collRect.size.y ? collRect.size.x : collRect.size.y;

		// step 4 - mind vector to move back by
		float minComp = 1;
		if (abs(_momentum.x) < abs(_momentum.y) && _momentum.x != 0) minComp = _momentum.x;
		else if (abs(_momentum.y) < abs(_momentum.x) && _momentum.y != 0) minComp = _momentum.y;
		
		sf::Vector2f moveVec;
		if (_momentum.x != 0 || _momentum.y != 0) {
			sf::Vector2f momNorm = _momentum;
			float length = momNorm.length();
			if (length > 0) {
				momNorm /= length;
			}

			moveVec = momNorm * collLen;
		}

		// step 5 - move by amount
		move(-moveVec);

		// step 6 - find vector to subtract from momentum
		sf::Vector2f sub;

		if (collRect.size.x > collRect.size.y) {
			sub = { 0, _momentum.y };
		}
		else if (collRect.size.y > collRect.size.x) {
			sub = { _momentum.x, 0 };
		}
		else {
			sub = { _momentum.x, _momentum.y };
		}

		_momentum -= sub;
	}
}

void PlayerBall::collideObstacles(std::vector<sf::ConvexShape> obstacles) {
	for (auto obst : obstacles) {
		std::vector<sf::Vector2f> intersectingPoints = findAllIntersections(*this, obst);
		if (intersectingPoints.size() > 0) {
			setScale({ 0.75f, 0.75f });
			applyCollisionForces(intersectingPoints, this);
			_momentum = sf::Vector2f();
			std::cout << "Intersecting points:" << std::endl;
			for (auto pt : intersectingPoints) {
				std::cout << pt << std::endl;
			}
		}
	}
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
		hasJumped = false;
	}

	setPosition({ newX, newY });
	_momentum = { newXMom, newYMom };
}

void PlayerBall::onCollide(Collidable& obj)
{
}
