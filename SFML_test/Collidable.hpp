#pragma once

#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// WE SHOULD MAKE A COLLIDEABLE CLASS AT SOME POINT
// WHICH WOULD BE INHERITED BY PLAYERS/WALLS/OBSTACLES
// it is not appropriate for this class to have this.
inline std::ostream& operator<<(std::ostream& lhs, const sf::Vector2f& rhs) {
    lhs << "<" << rhs.x << ", " << rhs.y << ">" << std::endl;
    return lhs;
}

class Collidable {
public:
    Collidable(std::string newTag);
    virtual void onCollide(Collidable& obj)=0;
    bool isInRange(const float& n, const float& bound1, const float& bound2);
    std::optional<sf::Vector2f> findIntersection(const float& x1, const float& y1, const float& x2, const float& y2, const float& x3, const float& y3, const float& x4, const float& y4);
    std::vector<sf::Vector2f> findAllIntersections(sf::Shape& a, sf::Shape& b);
    virtual void applyCollisionForces(const std::vector<sf::Vector2f>& intersections, sf::Shape* moveShape);

    std::string getTag();
    void setTag(std::string newTag);
private:
    std::string tag;
};