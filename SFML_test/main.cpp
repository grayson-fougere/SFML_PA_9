#include <iostream>
#include <vector>
#include "DebugCircle.hpp"
#include "CollisionHelper.hpp"

using std::cout;
using std::endl;


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
            std::vector<sf::Vector2f> intersects = CollisionHelper::findAllIntersections(shape, shape2);
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


