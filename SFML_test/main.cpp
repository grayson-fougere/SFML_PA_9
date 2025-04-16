#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Blue);
    window.setFramerateLimit(60); // sets max frame rate to 60fps

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

        window.clear();
        window.draw(shape);
        window.display();


        shape.move({ -1.f, 0.f });
    }
}