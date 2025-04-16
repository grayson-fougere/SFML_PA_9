#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);
    sf::CircleShape shape(100.f);
    sf::RectangleShape shape2({ 1600.f, 40.f });
    shape2.setFillColor(sf::Color::Blue);
    shape2.setPosition({ 0.f, 800.f });
    shape.setFillColor(sf::Color::Red);
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
        
        if (shape.getGlobalBounds().findIntersection(shape2.getGlobalBounds())) {
            //shape.setPosition({get})
            sf::Vector2f playerCurPos = shape.getPosition();
            sf::Vector2f objCurPos = shape2.getPosition();
            sf::Vector2f offset({ 0.f, -200.1f });
            shape.setPosition({ playerCurPos.x, objCurPos.y + offset.y });
            velocity.y = (0.f);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
                velocity += jump;
            }
        }
        else if (!shape.getGlobalBounds().findIntersection(shape2.getGlobalBounds()) && velocity.y < (35.f)) {
            velocity += gravity;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && velocity.x > -movementSpeedCap.x) {
            velocity -= movementSpeed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && velocity.x < movementSpeedCap.x) {
            velocity += movementSpeed;
        }

        //still need to add drag

        shape.move(velocity);

        
        window.clear();
        window.draw(shape);
        window.draw(shape2);
        window.display();
    }
}