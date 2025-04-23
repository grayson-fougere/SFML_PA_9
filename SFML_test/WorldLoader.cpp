#include "WorldLoader.hpp"

void WorldLoader::loadLevel(std::string levelName,	// what level to load. relative path.
	std::vector<Collidable*>& worldObjects,		// objects in world that inherit from Collidable
	std::vector<Coin>& coins,					// coins in world
	std::string& finishLoad,						// level to load when finish is reached
	std::vector<std::string>& otherLoads,		// levels to load when a load trigger is reached
	PlayerBall& player,							// player object, so coins can be reset and player position changed
	sf::RenderWindow& window,					// window object
	Camera& camera								// camera object, so camera can be adjusted to fit world
) {
	// open file and check for success
	std::ifstream levelFile(levelName);

	if (!levelFile.is_open()) {
		std::cerr << "Error opening level file \"" << levelName << "\"!" << std::endl;
		return;
	}

	// clear worldObjects
	for (auto obj : worldObjects) {
		delete obj;
	}
	worldObjects.clear();

	// flag: LEVEL reached
	bool levelReached = false;

	// constant: size of square objects
	float SQ_SIZE = player.getRadius() * 2;

	// go line by line
	std::string line;
	float cur_y = 0;
	while (std::getline(levelFile, line)) {
		if (line.rfind("LEVEL", 0) == 0) levelReached = true;
		
		if (!levelReached) {
			std::cout << "loaded level line: " << line << std::endl;

			std::istringstream rowChars(line);
			// go through the line's characters

			float cur_x = 0;
			while (rowChars.peek() != EOF) {
				// string to extract next block to
				std::string next;
				rowChars >> next;
				
				// special cases
				if (next[0] == 'z') {
					// put load trigger here
				}

				char block = next[0];  // single character block
				// normal blocks
				switch (block) {
					case '0': break;
					case '1': {
						std::cout << "placing platform at (" << cur_x << ", " << cur_y << ")" << std::endl;
						Platform* newPlatform = new Platform(sf::Vector2f(cur_x, cur_y), SQ_SIZE, SQ_SIZE, sf::Color::Green);
						worldObjects.push_back(newPlatform);
						break;
					}
					case 'p': {
						player.setPosition({ cur_x, cur_y });
						break;
					}
				}

				// increment x
				cur_x += SQ_SIZE;
			}

			cur_y += SQ_SIZE;
		}
		else {
			std::cout << "loaded load: " << line << std::endl;
		}
	}
}

