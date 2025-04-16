#pragma once
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// WE SHOULD MAKE A COLLIDEABLE CLASS AT SOME POINT
// WHICH WOULD BE INHERITED BY PLAYERS/WALLS/OBSTACLES
class CollisionHelper {
public:
    static bool isInRange(const float& n, const float& bound1, const float& bound2) {
        if (bound2 >= bound1) {
            return n >= bound1 && n <= bound2;
        }
        else {
            return n <= bound1 && n >= bound2;
        }
    }

    //https://en.wikipedia.org/wiki/Line–line_intersection
    static std::optional<sf::Vector2f> findIntersection(const float& x1, const float& y1, const float& x2, const float& y2,
        const float& x3, const float& y3, const float& x4, const float& y4) {
        float denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4), // denominator
            numerX = (x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4), // numerator of the X component of the intersection
            numerY = (x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4); // numerator of the Y component of the intersection
        if (denom != 0) {
            sf::Vector2f i(numerX / denom, numerY / denom);
            if (isInRange(i.x, x1, x2) && isInRange(i.x, x3, x4) && isInRange(i.y, y1, y2) && isInRange(i.y, y3, y4))
                return i;
            else return std::nullopt;
        }
        else {
            return std::nullopt;
        }
    }

    // Perhaps this should return a reference to help with performance
    static std::vector<sf::Vector2f> findAllIntersections(sf::Shape& a, sf::Shape& b)
    {
        std::vector<sf::Vector2f> intersects;
        for (int i = a.getPointCount() - 1; i >= 0; i--) {
            float x1 = a.getTransform().transformPoint(a.getPoint(i)).x, y1 = a.getTransform().transformPoint(a.getPoint(i)).y,
                x2 = a.getTransform().transformPoint(a.getPoint(i - 1)).x, y2 = a.getTransform().transformPoint(a.getPoint(i - 1)).y; // Start and end points of this edge
            if (i - 1 == -1) {
                x2 = a.getTransform().transformPoint(a.getPoint(a.getPointCount() - 1)).x, y2 = a.getTransform().transformPoint(a.getPoint(a.getPointCount() - 1)).y;
            }
            for (int j = b.getPointCount() - 1; j >= 0; j--) {
                float x3 = b.getTransform().transformPoint(b.getPoint(j)).x, y3 = b.getTransform().transformPoint(b.getPoint(j)).y,
                    x4 = b.getTransform().transformPoint(b.getPoint(j - 1)).x, y4 = b.getTransform().transformPoint(b.getPoint(j - 1)).y;
                if (j - 1 == -1) {
                    x4 = b.getTransform().transformPoint(b.getPoint(b.getPointCount() - 1)).x, y4 = b.getTransform().transformPoint(b.getPoint(b.getPointCount() - 1)).y;
                }
                std::optional v = findIntersection(x1, y1, x2, y2, x3, y3, x4, y4);
                if (v) {
                    intersects.push_back(v.value());
                    std::cout << v.value() << std::endl;
                }
            }
            //std::cout << i << std::endl;
        }
        return intersects;
    }
};

// it is not appropriate for this class to have this.
inline std::ostream& operator<<(std::ostream& lhs, const sf::Vector2f& rhs) {
    lhs << "<" << rhs.x << ", " << rhs.y << ">" << std::endl;
    return lhs;
}