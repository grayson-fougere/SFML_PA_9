#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "DebugCircle.hpp"

using std::cout;
using std::endl;

std::ostream& operator<<(std::ostream& lhs, const sf::Vector2f& rhs) {
    lhs << "<" << rhs.x << ", " << rhs.y << ">" << endl;
    return lhs;
}

//std::vector<sf::Vector2f> findAllIntersections(sf::CircleShape a, sf::RectangleShape b);
//std::vector<sf::Vector2f> findAllIntersections(sf::CircleShape a, sf::ConvexShape b);
std::vector<sf::Vector2f> findAllIntersections(sf::Shape& a, sf::Shape& b);
std::optional<sf::Vector2f> findIntersection(const float& x1, const float& y1, const float& x2, const float& y2, const float& x3, const float& y3, const float& x4, const float& y4);

bool isInRange(const float& n, const float& bound1, const float& bound2);

int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);
    //sf::CircleShape shape(100.f, 10);
    sf::RectangleShape shape({100, 100});
    shape.setPosition({ 200, 0 });
    shape.rotate(sf::degrees(45));
    sf::RectangleShape shape2({ 1600.f, 40.f });
    //sf::ConvexShape shape2(4);
    //shape2.setPoint(0, { 0, 500 });
    //shape2.setPoint(1, { 1000, 800 });
    //shape2.setPoint(2, { 1000, 2000 });
    //shape2.setPoint(3, { 0, 2000 });

    sf::RectangleShape colsqr({ 0.f, 0.f });
    DebugCircle colcirc1(5.f, 2.f);
    DebugCircle colcirc2(5.f,2.f);
    shape2.setFillColor(sf::Color::Blue);
    shape2.setPosition({ 0.f, 800.f });
    shape.setFillColor(sf::Color::Red);

    colsqr.setFillColor(sf::Color::Green);
    window.setFramerateLimit(60); // sets max frame rate to 60fps
    int test = 1;
    sf::Vector2f gravity({ 0.f, 3.f });
    sf::Vector2f velocity({ 0.f, 0.f });
    sf::Vector2f jump({ 0.f, -35.f });
    sf::Vector2f movementSpeed({ 7.f, 0.f });
    sf::Vector2f movementSpeedCap({ 30.f, 0.f });

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }


        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }


        std::optional intersect = shape.getGlobalBounds().findIntersection(shape2.getGlobalBounds());
        if (intersect) {
            std::vector<sf::Vector2f> intersects = findAllIntersections(shape, shape2);
            std::cout << "intersect size: " << intersects.size() << std::endl;
            //colcirc2.setPosition(shape.getTransform().transformPoint( shape.getPoint(shape.getPointCount()-1)) );
            if (intersects.size()!=0)colcirc1.setPosition(intersects[0]);
            if (intersects.size() > 1) {
                colcirc1.setPosition(intersects[0]);
                colcirc2.setPosition(intersects[1]);
            }
            colsqr.setPosition(intersect.value().position);
            colsqr.setSize(intersect.value().size);

            sf::Vector2f playerCurPos = shape.getPosition();
            sf::Vector2f objCurPos = shape2.getPosition();
            sf::Vector2f offset({ 0.f, -200.1f });
            //shape.setPosition({ playerCurPos.x, objCurPos.y + offset.y });
            velocity.y = (0.04f);
        }


        else if (!shape.getGlobalBounds().findIntersection(shape2.getGlobalBounds()) && velocity.y < (35.f)) {
            velocity += gravity;
        }

        //still need to add drag

        shape.move(velocity);

        window.clear();
        window.draw(shape);
        window.draw(shape2);
        //window.draw(colsqr);
        window.draw(colcirc1);
        window.draw(colcirc2);
        window.display();
    }
}


bool isInRange(const float &n, const float &bound1, const float &bound2) {
    if (bound2 >= bound1) {
        return n >= bound1 && n <= bound2;
    }
    else {
        return n <= bound1 && n >= bound2;
    }
}

//https://en.wikipedia.org/wiki/Line–line_intersection
std::optional<sf::Vector2f> findIntersection(const float &x1, const float& y1, const float& x2, const float& y2, 
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
std::vector<sf::Vector2f> findAllIntersections(sf::Shape& a, sf::Shape& b)
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
                cout << v.value() << endl;
            }
        }
        //std::cout << i << std::endl;
    }
    return intersects;
}
