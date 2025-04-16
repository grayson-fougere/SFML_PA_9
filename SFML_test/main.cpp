#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PlayerBall.hpp"

int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);
    PlayerBall player = PlayerBall(100, 0.75f, 50.f, 0.15f, {10.f, 10.f});
    sf::RectangleShape shape2({ 1600.f, 100.f });
    PlayerBall player = PlayerBall(100, 1.f, 35.f, 0.1f, {10.f, 10.f});
    sf::RectangleShape shape2({ 1600.f, 40.f });
    //sf::ConvexShape shape2(4);
    //shape2.setPoint(0, { 0, 500 });
    //shape2.setPoint(1, { 1000, 800 });
    //shape2.setPoint(2, { 1000, 2000 });
    //shape2.setPoint(3, { 0, 2000 });

    sf::RectangleShape colsqr({ 0.f, 0.f });
    // DebugCircle colcirc1(5.f, 2.f);
    // DebugCircle colcirc2(5.f,2.f);
    shape2.setFillColor(sf::Color::Blue);
    shape2.setPosition({ 0.f, 800.f });
    sf::RectangleShape shape3({ 50.f, 500.f });
    shape3.setFillColor(sf::Color::Green);
    shape3.setPosition({ 1200.f, 0.f });
    window.setFramerateLimit(60); // sets max frame rate to 60fps
    int test = 1;

    sf::Clock deltaTimeClock;

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

        int32_t dt = deltaTimeClock.restart().asMilliseconds();
        player.update(dt);

        std::vector<sf::FloatRect> collisionBoxes;
        collisionBoxes.push_back(shape2.getGlobalBounds());
        collisionBoxes.push_back(shape3.getGlobalBounds());

        player.collide(collisionBoxes);

        //player.collideTop(shape2);
        player.collideView(window.getSize());
        
        //if (shape.getGlobalBounds().findIntersection(shape2.getGlobalBounds())) {
        //    //shape.setPosition({get})
        //    sf::Vector2f playerCurPos = shape.getPosition();
        //    sf::Vector2f objCurPos = shape2.getPosition();
        //    sf::Vector2f offset({ 0.f, -200.1f });
        //    shape.setPosition({ playerCurPos.x, objCurPos.y + offset.y });
        //    velocity.y = (0.f);
        //    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        //        velocity += jump;
        //    }
        //}
        //else if (!shape.getGlobalBounds().findIntersection(shape2.getGlobalBounds()) && velocity.y < (35.f)) {
        //    velocity += gravity;
        //}
        //
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && velocity.x > -movementSpeedCap.x) {
        //    velocity -= movementSpeed;
        //}
        //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && velocity.x < movementSpeedCap.x) {
        //    velocity += movementSpeed;
        //}

        //still need to add drag

        //shape.move(velocity);

        window.clear();
        window.draw(player);
        window.draw(shape2);
        window.draw(shape3);
        //window.draw(colsqr);
        // window.draw(colcirc1);
        // window.draw(colcirc2);
        window.display();
    }
}


