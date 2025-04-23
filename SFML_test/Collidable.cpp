#include "Collidable.hpp"

Collidable::Collidable(std::string newTag)
{
    this->tag = newTag;
}

float Collidable::distanceBetween(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

bool Collidable::isInRange(const float& n, const float& bound1, const float& bound2) {
    if (bound2 >= bound1) {
        return n >= bound1 && n <= bound2;
    }
    else {
        return n <= bound1 && n >= bound2;
    }
}

//https://en.wikipedia.org/wiki/Line–line_intersection
std::optional<sf::Vector2f> Collidable::findIntersection(const float& x1, const float& y1, const float& x2, const float& y2,
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
std::vector<sf::Vector2f> Collidable::findAllIntersections(sf::Shape& a, sf::Shape& b)
{
    std::vector<sf::Vector2f> intersects;
    for (int i = a.getPointCount() - 1; i >= 0; i--) {
        const sf::Vector2f& p1 = a.getPoint(i), & p2 = (i > 0) ? a.getPoint(i - 1) : a.getPoint(a.getPointCount() - 1);
        float x1 = a.getTransform().transformPoint(a.getPoint(i)).x, y1 = a.getTransform().transformPoint(a.getPoint(i)).y,

            x2 = a.getTransform().transformPoint(a.getPoint(i - 1)).x, y2 = a.getTransform().transformPoint(a.getPoint(i - 1)).y; // Start and end points of this edge
        for (int j = b.getPointCount() - 1; j >= 0; j--) {
            const sf::Vector2f& p1 = b.getPoint(j), & p2 = (j > 0) ? b.getPoint(j - 1) : b.getPoint(b.getPointCount() - 1);
            float x3 = b.getTransform().transformPoint(b.getPoint(j)).x, y3 = b.getTransform().transformPoint(b.getPoint(j)).y,
                x4 = b.getTransform().transformPoint(p2).x, y4 = b.getTransform().transformPoint(p2).y;

            std::optional v = findIntersection(x1, y1, x2, y2, x3, y3, x4, y4);
            if (v) {
                intersects.push_back(v.value());
            }
        }
    }
    Collidable* b_col = dynamic_cast<Collidable*>(&b);
    //std::cout << (b_col == nullptr) << std::endl;
    if (intersects.size() > 0 && b_col) {
        onCollide(b_col);
    }
    return intersects;
}



sf::Vector2f Collidable::applyCollisionForces(const std::vector<sf::Vector2f>& intersections, sf::Shape* moveShape)
{
    if (intersections.size() >= 2) {
        const sf::Vector2f& p1 = intersections[0], & p2 = intersections[1], diff = p2 - p1, mid = p1 + (diff * 0.5f), norm = diff.perpendicular(),
            shapeCenter = moveShape->getTransform().transformPoint(moveShape->getGeometricCenter());
        //float moveSize = (mid - moveShape->getTransform().transformPoint(moveShape->getGeometricCenter())).length();
        //float moveMagnitude = 15;
        float moveMagnitude = distanceBetween(p1, shapeCenter) - distanceBetween(mid, shapeCenter);
        if (distanceBetween(mid + norm.normalized() * moveMagnitude, shapeCenter) > 
            distanceBetween(mid + norm.normalized() * -moveMagnitude, shapeCenter)) {
            moveMagnitude *= -1;
        }
        moveShape->move(norm.normalized()*moveMagnitude);
        return norm.normalized() * moveMagnitude;
    }
}

std::string Collidable::getTag()
{
    return tag;
}

void Collidable::setTag(std::string newTag) {
    tag = newTag;
}
