#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "PlayerBall.hpp"
#include "Background.hpp"
#include "coin.hpp"
#include <random>
#include <sstream>
#include "Camera.hpp"
#include "Spike.hpp"
#include "Obstacle.hpp"
#include "WorldLoader.hpp"
#include "Platform.hpp"
#include <optional>
#include <SFML/Audio.hpp>

int main()
{
    /* ----- Main Window ----- */
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);  // sf window to draw to

    /* ---- Fonts ----- */
    sf::Font font("Resources/freedom-font.ttf");

    /* ----- Background ----- */
    Background WorldBackground;
    WorldBackground.resize(window.getSize());

    /* ----- Player ----- */
    PlayerBall player = PlayerBall(100, 0.125f, 5.f, 0.15f, { 10.f, 10.f });

    /* ----- Camera ----- */
    Camera viewCam(window);

    viewCam.setCoinCounterOffset(sf::Vector2f(175, 1.5));
    viewCam.setCoinSpriteOffset(sf::Vector2f(300, 10));
    viewCam.updatePlayer(player);
    viewCam.followPlayer();

    /* ----- Coin Icon ----- */
    sf::Image coinImage;
    sf::Texture coinTexture;

    // Load image
    if (!coinImage.loadFromFile("Textures/coinpicture.png")) {
        return -1; // Error handling
    }

    // Load texture from image
    if (!coinTexture.loadFromImage(coinImage)) {
        return -1; // Error handling
    }

    sf::Sprite coinIcon(coinTexture);
    coinIcon.setScale(sf::Vector2f(0.2f, 0.2f)); // Smaller than the main coins

    /* ----- Coin Counter Text ----- */
    sf::Text coinCounterText(font);

    coinCounterText.setFont(font);
    coinCounterText.setString("00");
    coinCounterText.setCharacterSize(100);
    coinCounterText.setFillColor(sf::Color::White);

    /* ----- Sounds ----- */
    sf::Music backgroundMusic;
    sf::SoundBuffer coinBuffer;
    std::optional<sf::Sound> coinSound;
    sf::SoundBuffer jumpBuffer;

    // background music
    if (!backgroundMusic.openFromFile("Resources/Gamesong.mp3")) { // All rights go to ConcernedApe and Chucklefish (Music from Stardew Valley)
        std::cerr << "Failed to load background music!\n";
    }
    else {
        backgroundMusic.setLooping(true);       // Loop indefinitely
        backgroundMusic.setVolume(80.f);
        backgroundMusic.play();              // Start song
    }

    // coins
    if (coinBuffer.loadFromFile("Resources/coin.wav")) {
        coinSound.emplace(coinBuffer);
        coinSound->setVolume(25);
    }

    // jumps
    if (jumpBuffer.loadFromFile("Resources/jump.wav")) {
        player.setJumpSound(jumpBuffer);  // Pass to player
    }
    else {
        std::cout << "Couldn't load jump sound\n";
    }

    /* ----- DeltaTime Clock ----- */
    sf::Clock deltaTimeClock;

    /* ----- World Objects ----- */
    std::vector<Coin> coins;
    std::vector<Collidable*> worldObjects;
    std::string finishLoad;
    std::vector<std::string> otherLoads;

    /* ----- NEW WORLD LOADING ----- */
    WorldLoader::loadLevel("LevelSelect.txt", worldObjects, coins, finishLoad, otherLoads, player, window, viewCam);

    std::vector<Platform*> platforms;
    for (auto obj : worldObjects) {
        Platform* platform_ptr = dynamic_cast<Platform*>(obj);
        if (platform_ptr != nullptr) {
            platforms.push_back(platform_ptr);
        }
    }

    /* ----- OLD WORLD STUFF ----- */

    //bool coinActive = true;

    //// Initialize coins
    //coins.emplace_back(coinTexture, sf::Vector2f(window.getSize().x - 2100.f, window.getSize().y - 1500.f));
    //coins.emplace_back(coinTexture, sf::Vector2f(800.f, 600.f));
    //coins.emplace_back(coinTexture, sf::Vector2f(1200.f, 400.f));
    //
    //sf::RectangleShape shape2({ 1600.f, 100.f });
    //sf::RectangleShape colsqr({ 0.f, 0.f });

    //Obstacle obs1({100, 100}, {300, 1000});
    ////sf::RectangleShape colsqr({ 100.f, 100.f });
    //sf::ConvexShape trasnejdks(3);
    //trasnejdks.setPoint(0, { 0.f, 0.f });
    //trasnejdks.setPoint(1, { 100.f, 0.f });
    //trasnejdks.setPoint(2, { 0.f, -100.f });
    //trasnejdks.setFillColor(sf::Color::Red);
    //trasnejdks.setScale({ 2.5f, 2.5f });
    //trasnejdks.setPosition({ 0, 1800 });

    //shape2.setFillColor(sf::Color::Blue);
    //shape2.setPosition({ 0.f, 800.f });
    //sf::RectangleShape shape3({ 50.f, 500.f });
    //shape3.setFillColor(sf::Color::Green);
    //shape3.setPosition({ 1200.f, 0.f });

    //sf::ConvexShape trianslkgb(3);
    //trianslkgb.setPoint(0, { 0, 50 });
    //trianslkgb.setPoint(1, { 50, 50 });
    //trianslkgb.setPoint(2, { 25, 0 });
    //trianslkgb.setFillColor(sf::Color::Green);
    //trianslkgb.setScale({ 5.f, 5.f });
    //trianslkgb.setPosition({ 800, 700 });

    //Spike spike({ 1000, 1000 }, 10);
    //Platform plat1(sf::Vector2f(3000.f, 1000.f), 1000, 1000, sf::Color::Magenta);
    //window.setFramerateLimit(60); // sets max frame rate to 60fps

    //std::vector<sf::Shape*> obstacles;
    //std::vector<sf::Shape*> platforms;
    //obstacles.push_back(&trasnejdks);
    //obstacles.push_back(&obs1);
    //obstacles.push_back(&spike);

    //platforms.push_back(&plat1);

    /* ----- Main Loop ----- */
    while (window.isOpen())
    {
        // check for quit button (esc)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
            window.close();
        }

        // check for close button press [X]
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        /* ----- Get DeltaTime -----*/
        sf::Time dtClockRestart = deltaTimeClock.restart();
        int32_t dt_ms = dtClockRestart.asMilliseconds();
        float dt_s = dtClockRestart.asSeconds();

        /* ----- Update Player ----- */
        player.update(dt_ms);

        /* ----- Update World Background (Parallax and Tiling) ----- */
        float playerMovement = player.getMomentum().x * dt_s;
        WorldBackground.scroll(-playerMovement * 1.f);

        /* ----- Collect coins ----- */
        for (int i = 0; i < coins.size(); i++) {
            if (player.getGlobalBounds().findIntersection(coins[i].getSprite().getGlobalBounds())) {
                if (coinSound.has_value()) {
                    coinSound->play();
                }
                player.incrementCoins();
                coins.erase(coins.begin() + i);
                i--; // Adjust index after removal of the vector


                // formatted the counter to keep the 0
                std::stringstream ss;
                ss << std::setw(2) << std::setfill('0') << player.getNumCoins();
                coinCounterText.setString(ss.str());

                

                break; // Exit after collecting one coin per frame
            }
        }

        /* ----- Handle Collisions ----- */
        std::vector<sf::FloatRect> collisionBoxes;
        //collisionBoxes.push_back(shape2.getGlobalBounds());
        //collisionBoxes.push_back(shape3.getGlobalBounds());

        player.collide(collisionBoxes);

        // These should prob be merged?
        //player.collideObstacles(obstacles);
        player.collidePlatorms(platforms);

        /* ----- Update Camera, Coin Icon, & Coin Text ----- */
        viewCam.update();
        window.setView(viewCam);

        coinCounterText.setPosition(viewCam.getCoinCounterPos());
        coinIcon.setPosition(viewCam.getCoinSpritePos());

        /* ----- Window Re-drawing ----- */
        window.clear();
        WorldBackground.draw(window);
        for (auto obj : worldObjects) {
            sf::Drawable* d_obj = dynamic_cast<sf::Drawable*>(obj);
            if (d_obj != nullptr) {
                window.draw(*d_obj);
            }
        }
        window.draw(player);
        //window.draw(shape2);
        //window.draw(shape3);
        for (auto& coin : coins) {
            window.draw(coin.getSprite());
        }
        window.draw(coinCounterText);
        //window.draw(spike);
        //window.draw(obs1);
        //window.draw(plat1);
        window.draw(coinIcon);
        //window.draw(trasnejdks);
        window.display();
    }
}
