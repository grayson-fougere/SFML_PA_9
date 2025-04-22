#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PlayerBall.hpp"
#include "Background.hpp"
#include "coin.hpp"
#include <random>
#include <sstream>
int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);


    sf::Image coinImage;
    if (!coinImage.loadFromFile("Textures/coinpicture.png")) {
        return -1; // Error handling
    }

    sf::Texture coinTexture;
    if (!coinTexture.loadFromImage(coinImage)) {
        return -1; // Error handling
    }


    Background WorldBackground; 
    WorldBackground.resize(window.getSize()); 
    PlayerBall player = PlayerBall(100, 0.75f, 5.f, 0.15f, {10.f, 10.f});

    // --- COIN SYSTEM ---
    std::vector<Coin> coins;
    int coinCount = 0;

    // Randomly place a coin
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(50, window.getSize().x - 50);
    std::uniform_int_distribution<> yDist(50, window.getSize().y - 50);

    coins.emplace_back(coinTexture, xDist(gen), yDist(gen));

    // --- COIN COUNTER (Text + Sprite) ---
    sf::Font font;

    // ******* removed logic to add a font, add that later


    sf::Text coinCounterText(font);
    coinCounterText.setString("0");
    coinCounterText.setCharacterSize(30);
    coinCounterText.setFillColor(sf::Color::Yellow);
    coinCounterText.setPosition(sf::Vector2f(
        static_cast<float>(window.getSize().x) - 120.f, 20.f)); // so the values can convert

    // Mini coin sprite next to the counter
    sf::Sprite coinIcon(coinTexture);
    coinIcon.setScale(sf::Vector2f(0.5f, 0.5f)); // Smaller than the main coins
    coinIcon.setPosition(sf::Vector2f(
        static_cast<float>(window.getSize().x) - 50.f, 20.f));
    
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

        float deltaTime = deltaTimeClock.restart().asSeconds();
        float playerMovement = player.getMomentum().x * deltaTime;
        WorldBackground.scroll(-playerMovement * 0.5f);

        std::vector<sf::FloatRect> collisionBoxes;
        collisionBoxes.push_back(shape2.getGlobalBounds());
        collisionBoxes.push_back(shape3.getGlobalBounds());

        player.collide(collisionBoxes);

        //player.collideTop(shape2);
        player.collideView(window.getSize());

        //still need to add drag

        //shape.move(velocity);

        window.clear();
        WorldBackground.draw(window);
        window.draw(player);
        window.draw(shape2);
        window.draw(shape3);
        window.draw(coinIcon);
        //window.draw(colsqr);
        // window.draw(colcirc1);
        // window.draw(colcirc2);
        window.display();
    }
}


