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
#include "TestCases.hpp"
#include <optional>
#include <SFML/Audio.hpp>

int main()
{
    // Test cases
    TestCases::runAll();
    /* ----- Main Window ----- */
    sf::RenderWindow window(sf::VideoMode({ 200, 200 }), "SFML works!", sf::State::Fullscreen);  // sf window to draw to
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

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
    std::vector<sf::Shape*> collisionStuffs;

    /* ----- World Objects ----- */
    std::vector<Coin*> coins;
    std::vector<Collidable*> worldObjects;
    std::string finishLoad;
    std::vector<std::string> otherLoads;

    /* ----- NEW WORLD LOADING ----- */
    WorldLoader::loadLevel("Level1.txt", worldObjects, coins, finishLoad, otherLoads, player, window, viewCam, coinTexture);

    std::vector<sf::Shape*> platforms;
    for (auto obj : worldObjects) {
        Platform* platform_ptr = dynamic_cast<Platform*>(obj);
        if (platform_ptr != nullptr) {
            platforms.push_back(platform_ptr);
        }
    }

    std::vector <sf::Shape*> spikes;
    for (auto obj : worldObjects) {
        Spike* spike_ptr = dynamic_cast<Spike*>(obj);
        if (spike_ptr != nullptr) {
            spikes.push_back(spike_ptr);
        }
    }

  

    
    bool mainMenuOpen = true;
    int optionSelected = 0;
    sf::Text gameTitle(font, "Red Ball", 70);
    sf::Text playButton(font, "Play", 48);
    sf::Text creditsButton(font, "Credits", 48);
    sf::Text exitButton(font, "Exit", 48);
    sf::Text creditsTitle(font, "Game Created By:", 140);
    sf::Text logkenCredits(font, "Logan Meyers,   Kenny Hussey", 70);
    sf::Text magraCredits(font, "Mason Nagel,     Grayson Fougere", 70);
    sf::Text backButton(font, "Back", 48);
    sf::Text howToPlay(font, "To move sideways A/D | To move up W/Space", 30);
    sf::Text deathTitle(font, "Death comes for us all", 60);
    sf::Text winScreen(font, "Congrats", 200);
    sf::Text nextLevelButton(font, "Next Level", 75);

    //changes origin of text boxes to center so when changing position it is in the center of the screen
    gameTitle.setOrigin({ gameTitle.getGlobalBounds().getCenter().x, gameTitle.getGlobalBounds().getCenter().y });
    playButton.setOrigin({ playButton.getGlobalBounds().getCenter().x, playButton.getGlobalBounds().getCenter().y });
    creditsButton.setOrigin({ creditsButton.getGlobalBounds().getCenter().x, creditsButton.getGlobalBounds().getCenter().y });
    exitButton.setOrigin({ exitButton.getGlobalBounds().getCenter().x, exitButton.getGlobalBounds().getCenter().y });
    creditsTitle.setOrigin({ creditsTitle.getGlobalBounds().getCenter().x, creditsTitle.getGlobalBounds().getCenter().y });
    logkenCredits.setOrigin({ logkenCredits.getGlobalBounds().getCenter().x, logkenCredits.getGlobalBounds().getCenter().y });
    magraCredits.setOrigin({ magraCredits.getGlobalBounds().getCenter().x, magraCredits.getGlobalBounds().getCenter().y });
    backButton.setOrigin({ backButton.getGlobalBounds().getCenter().x, backButton.getGlobalBounds().getCenter().y });
    howToPlay.setOrigin({ howToPlay.getGlobalBounds().getCenter().x, howToPlay.getGlobalBounds().getCenter().y });
    winScreen.setOrigin({ winScreen.getGlobalBounds().getCenter().x, winScreen.getGlobalBounds().getCenter().y });
    nextLevelButton.setOrigin({ nextLevelButton.getGlobalBounds().getCenter().x, nextLevelButton.getGlobalBounds().getCenter().y });


    //sets position of the text boxes
    gameTitle.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f - 200});
    playButton.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f - 75});
    creditsButton.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f});
    exitButton.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f + 75 });
    creditsTitle.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f - 200 });
    logkenCredits.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f - 75 });
    magraCredits.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f });
    backButton.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f + 150});
    howToPlay.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f + 200 });
    winScreen.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f - 150 });
    nextLevelButton.setPosition({ static_cast<float>(window.getSize().x) / 2.f, static_cast<float>(window.getSize().y) / 2.f + 200 });


    winScreen.setFillColor(sf::Color::Green);
    howToPlay.setFillColor(sf::Color::Red);

    /* ----- Main Loop ----- */
    while (window.isOpen())
    {
        
        //when main menu is open
        if (mainMenuOpen == true && optionSelected == 0) {
            window.clear();
            window.draw(gameTitle);
            window.draw(playButton);
            window.draw(creditsButton);
            window.draw(exitButton);
            window.draw(howToPlay);

            if (playButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition()))) {
                playButton.setFillColor(sf::Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    mainMenuOpen = false;
                    optionSelected = 1;
                }
            }
            else { playButton.setFillColor(sf::Color::White); }
            if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition()))) {
                exitButton.setFillColor(sf::Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    window.close();
                }
            }
            else { exitButton.setFillColor(sf::Color::White); }
            if (creditsButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition()))) {
                creditsButton.setFillColor(sf::Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    optionSelected = 2;
                    mainMenuOpen = false;
                }
            }
            else { creditsButton.setFillColor(sf::Color::White); }
        }


        //credits open
        if (optionSelected == 2) {
            window.clear();
            window.draw(backButton);
            window.draw(logkenCredits);
            window.draw(magraCredits);
            window.draw(creditsTitle);

            if (backButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition()))) {
                backButton.setFillColor(sf::Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    mainMenuOpen = true;
                    optionSelected = 0;
                }
            }
            else { backButton.setFillColor(sf::Color::White); }
        }

        //if won
        if (optionSelected == 2) {
            
            window.clear();
            window.draw(winScreen);
            window.draw(exitButton);
            


            if (exitButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition()))) {
                exitButton.setFillColor(sf::Color::Red);
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    window.close();
                }
            }
            else { exitButton.setFillColor(sf::Color::White); }
        }



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



        //when play is selected and first level
        if (optionSelected == 1) {
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
                if (player.getGlobalBounds().findIntersection((coins[i])->getSprite().getGlobalBounds())) {
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


            if (coins.size() <= 0) {
                optionSelected = 3;
            }


            /* ----- Handle Collisions ----- */
            std::vector<sf::FloatRect> collisionBoxes;

            player.collide(collisionBoxes);

        // These should prob be merged?
        //player.collideObjects(collisionStuffs); // Shift to the use of this!
        player.collideObjects(spikes);
        player.collideObjects(platforms);

            /* ----- Update Camera, Coin Icon, & Coin Text ----- */
            viewCam.update();
            window.setView(viewCam);

            coinCounterText.setPosition(viewCam.getCoinCounterPos());
            coinIcon.setPosition(viewCam.getCoinSpritePos());

            /* ----- Window Re-drawing ----- */
            window.clear();
            WorldBackground.draw(window, viewCam);
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
                window.draw(coin->getSprite());
            }
            window.draw(coinCounterText);
            //window.draw(spike);
            //window.draw(obs1);
            //window.draw(plat1);
            window.draw(coinIcon);
            //window.draw(trasnejdks);

            //flag.draw(window);
        }


        window.display();
    }
}
