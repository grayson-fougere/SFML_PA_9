#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PlayerBall.hpp"
#include "Background.hpp"
#include "Camera.hpp"
int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);

    Camera viewCam(window);

    Background WorldBackground;
    WorldBackground.resize(window.getSize());
    PlayerBall player = PlayerBall(100, 0.25f, 5.f, 0.15f, {10.f, 10.f});

    sf::RectangleShape shape2({ 1600.f, 100.f });

    //sf::RectangleShape colsqr({ 100.f, 100.f });
    sf::ConvexShape trasnejdks(3);
    trasnejdks.setPoint(0, { 0.f, 0.f });
    trasnejdks.setPoint(1, { 100.f, 0.f });
    trasnejdks.setPoint(2, { 0.f, -100.f });
    trasnejdks.setFillColor(sf::Color::Red);
    trasnejdks.setScale({ 2.5f, 2.5f });
    trasnejdks.setPosition({ 0, 1800 });
    shape2.setFillColor(sf::Color::Blue);
    shape2.setPosition({ 0.f, 800.f });
    sf::RectangleShape shape3({ 50.f, 500.f });
    shape3.setFillColor(sf::Color::Green);
    shape3.setPosition({ 1200.f, 0.f });

    sf::ConvexShape trianslkgb(3);
    trianslkgb.setPoint(0, { 0, 50 });
    trianslkgb.setPoint(1, { 50, 50 });
    trianslkgb.setPoint(2, { 25, 0 });
    trianslkgb.setFillColor(sf::Color::Green);
    trianslkgb.setScale({ 3.f, 3.f });
    trianslkgb.setPosition({ 800, 700 });

    window.setFramerateLimit(60); // sets max frame rate to 60fps

    sf::Clock deltaTimeClock;

    std::vector<sf::ConvexShape> obstacles;
    obstacles.push_back(trianslkgb);
    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            viewCam.setStaticTarget(sf::Vector2f( window.getSize().x / 2, window.getSize().y / 2 ));
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            viewCam.setDynamicTarget(player);
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

        std::vector<sf::ConvexShape> obstacles;
        //obstacles.push_back(trianslkgb);
        obstacles.push_back(trasnejdks);

        player.collideObstacles(obstacles);

        //player.collideTop(shape2);
        player.collideView(window.getSize());

        //still need to add drag

        //shape.move(velocity);

        viewCam.update();
        window.setView(viewCam);

        window.clear();
        WorldBackground.draw(window);
        window.draw(player);
        window.draw(shape2);
        window.draw(shape3);
        //window.draw(trianslkgb);
        window.draw(trasnejdks);
        // window.draw(colcirc1);
        // window.draw(colcirc2);
        window.display();
    }
}


