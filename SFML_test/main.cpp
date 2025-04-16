#include <SFML/Graphics.hpp>
#include "PlayerBall.hpp"
#include "Obstacle.hpp"
#include <vector>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1000, 1000}), "SFML_test Game");

    std::vector<Obstacle*> obstacles;

    // some obstacles
    obstacles.push_back(new Obstacle({ 1000, 20 }, { 0, 0 })); // top border
    obstacles.push_back(new Obstacle({ 20, 1000 }, { 0, 0 })); // left border
    obstacles.push_back(new Obstacle({ 20, 1000 }, { 980, 0 })); // right border
    obstacles.push_back(new Obstacle({ 1000, 20 }, { 0, 980 })); // bottom border

    // player ball
    PlayerBall player = PlayerBall(30, .01);
    player.setPosition({ 500, 500 });

    sf::Clock deltaClock;

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        int32_t dt = deltaClock.restart().asMilliseconds();

        // update objects
        player.update(dt);

        // perform collision checks for player
        std::vector<sf::FloatRect> obstBoxes;
        for (auto obst : obstacles) {
            obstBoxes.push_back(obst->getGlobalBounds());
        }
        player.collide(obstBoxes);

        std::cout << player.getPosition().x << " " << player.getPosition().y << std::endl;

        //for (auto obj : gameObjs) {
            //obj->update();
        //}

        window.clear();

        for (auto obst : obstacles) {
            window.draw(*obst);
        }

        window.draw(player);
        window.display();
    }
}