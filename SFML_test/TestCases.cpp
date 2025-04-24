#include "TestCases.hpp"

void TestCases::TestSetNumCoinsplayer() {
	PlayerBall player(10.0f);
	player.setNumCoins(5);
	std::cout << "Expected coins: 5, Got: " << player.getNumCoins() << "\n";
}

void TestCases::TestIncrementCoins() {
    PlayerBall ball(10.f);
    ball.incrementCoins();
    ball.incrementCoins();
    std::cout << "Expecting numCoins = 2 -> " << ball.getNumCoins() << "\n";
}

void TestCases::TestPlatformCreation() {
    std::cout << "\nTesting Platform Basics... \n\n";

    // create a test platform
    sf::Vector2f position(100, 200);  
    float width = 300;
    float height = 50;
    Platform testPlatform(position, width, height, sf::Color::Green);

    // check if size was set correctly
    sf::Vector2f platformSize = testPlatform.getSize();
    std::cout << "Size Test:\n";
    std::cout << "Expected: (" << width << ", " << height << ")\n";
    std::cout << "Actual: (" << platformSize.x << ", " << platformSize.y << ")\n";
    if (platformSize.x == width && platformSize.y == height) {
        std::cout << " Passed!\n";
    }
    else {
        std::cout << "Failed!\n";
    }

    // check if position was set correctly
    sf::Vector2f platformPos = testPlatform.getPosition();
    std::cout << "\nPosition Test:\n";
    std::cout << "  Expected: (" << position.x << ", " << position.y << ")\n";
    std::cout << "  Actual: (" << platformPos.x << ", " << platformPos.y << ")\n";
    if (platformPos == position) {
        std::cout << "Passed!\n";
    }
    else {
        std::cout << "Failed!\n";
    }

    // 4check if color was set
    std::cout << "\nColor Test:\n";
    if (testPlatform.getFillColor() == sf::Color::Green) {
        std::cout << "Color is green (passed)\n";
    }
    else {
        std::cout << "Wrong color\n";
    }
}

void TestCases::TestBackgroundScroll() {
    std::cout << "--- Scroll Test ---\n";
    Background bg;

    // Scroll and check
    bg.scroll(10.0f);
    bg.scroll(-5.0f);

    // if no errors when scroll runs then pass

    std::cout << "PASS: Scroll executed aka no crash)\n";
}

void TestCases::TestBackgroundBasic() {
    std::cout << "Background Basic Test\n";
    Background bg; // Just test constructor
    std::cout << "PASS: Background initialized ala no crash\n";
}

void TestCases::runAll() {
    TestSetNumCoinsplayer();
    TestIncrementCoins();
    TestPlatformCreation();
}