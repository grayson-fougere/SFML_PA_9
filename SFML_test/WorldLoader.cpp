#include "WorldLoader.hpp"

void WorldLoader::loadLevel(std::string levelName,	// what level to load. relative path.
	std::vector<Collidable>& worldObjects,		// objects in world that inherit from Collidable
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
	worldObjects.clear();

	// flag: LEVEL reached
	bool levelReached = false;

	// go line by line
	std::string line;
	while (std::getline(levelFile, line)) {
		if (line.rfind("LEVEL", 0) == 0) levelReached = true;
		
		if (!levelReached) {
			std::cout << "loaded level line: " << line << std::endl;
		}
		else {
			std::cout << "loaded load: " << line << std::endl;
		}
	}
}

