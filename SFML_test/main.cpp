#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PlayerBall.hpp"
#include "Background.hpp"
#include "coin.hpp"
#include <random>
#include <sstream>
#include "Camera.hpp"
#include "Obstacle.hpp"
int main()
{
    //sf::Window App
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);

    // opens a font
    sf::Font font("Resources/freedom-font.ttf");

    sf::Image coinImage;
    if (!coinImage.loadFromFile("Textures/coinpicture.png")) {
        return -1; // Error handling
    }

    sf::Texture coinTexture;
    if (!coinTexture.loadFromImage(coinImage)) {
        return -1; // Error handling
    }
    
    Camera viewCam(window);

    Background WorldBackground;
    WorldBackground.resize(window.getSize());
    PlayerBall player = PlayerBall(100, 0.25f, 5.f, 0.15f, {10.f, 10.f});

    // --- COIN SYSTEM ---
    std::vector<Coin> coins;
    int coinCount = 0;


    // placing a coin
    sf::Sprite coin1(coinTexture);
    coin1.setScale(sf::Vector2f(0.3f, 0.3f)); // main coin size
    coin1.setPosition(sf::Vector2f(static_cast<float>(window.getSize().x) -2100.f, window.getSize().y - 1500.f));


    // font placement logic
    sf::Text coinCounterText(font);
    coinCounterText.setFont(font);
    coinCounterText.setString("00");
    coinCounterText.setCharacterSize(100);
    coinCounterText.setFillColor(sf::Color::White);
    // call setCoinCounterOffset here and add a vector of 175 and 1.5

    // Mini coin sprite next to the counter
    sf::Sprite coinIcon(coinTexture);
    coinIcon.setScale(sf::Vector2f(0.2f, 0.2f)); // Smaller than the main coins
    // call setCoinSpriteOffset here and add a vector of 300 and 10
    
    sf::RectangleShape shape2({ 1600.f, 100.f });
    sf::RectangleShape colsqr({ 0.f, 0.f });


    Obstacle obs1({100, 100}, {300, 1000});
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
    trianslkgb.setScale({ 5.f, 5.f });
    trianslkgb.setPosition({ 800, 700 });

    window.setFramerateLimit(60); // sets max frame rate to 60fps

    sf::Clock deltaTimeClock;

    std::vector<sf::Shape*> obstacles;
    obstacles.push_back(&trasnejdks);
    obstacles.push_back(&obs1);

    viewCam.updatePlayer(player);

    while (window.isOpen())
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            viewCam.updateStaticPos({ 0.f, 0.f });
            viewCam.followStatic();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            viewCam.followPlayer();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            viewCam.updateStaticCenter({ 0.f, 0.f });
            viewCam.followStatic();
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

        //obstacles.push_back(trianslkgb);

        player.collideObstacles(obstacles);

        //player.collideTop(shape2);
        player.collideView(window.getSize());

        //still need to add drag

        //shape.move(velocity);

        viewCam.update();
        window.setView(viewCam);

        // set coin sprite pos, coin counter pos, and counter text by calling the corresponding functions from Camera and Player

        window.clear();
        WorldBackground.draw(window);
        window.draw(player);
        window.draw(shape2);
        window.draw(shape3);
        window.draw(coin1);
        window.draw(coinCounterText);
        window.draw(obs1);
        window.draw(coinIcon);
        //window.draw(colsqr);
        //window.draw(trianslkgb);
        window.draw(trasnejdks);
        // window.draw(colcirc1);
        // window.draw(colcirc2);
        window.display();
    }
}


