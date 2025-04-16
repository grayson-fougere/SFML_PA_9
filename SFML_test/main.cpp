#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PlayerBall.hpp"

int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);
    PlayerBall player = PlayerBall(100, 0.75f, 5.f, 0.15f, {10.f, 10.f});
    sf::RectangleShape shape2({ 1600.f, 100.f });

    sf::RectangleShape colsqr({ 0.f, 0.f });
    shape2.setFillColor(sf::Color::Blue);
    shape2.setPosition({ 0.f, 800.f });
    sf::RectangleShape shape3({ 50.f, 500.f });
    shape3.setFillColor(sf::Color::Green);
    shape3.setPosition({ 1200.f, 0.f });
    window.setFramerateLimit(60); // sets max frame rate to 60fps

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


