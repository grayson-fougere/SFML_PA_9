#include <SFML/Graphics.hpp>
#include "Collidable.hpp"
#include "PlayerBall.hpp"
#include "coin.hpp"
#include "Camera.hpp"
#include <fstream>
#include <sstream>
#include "Platform.hpp"

/*
What the characters mean in a level file:

l [LEFT EDGE]: clamp camera from moving past that left
r [RIGHT EDGE]: clamp camera from movign past that right
0 [AIR]: no block here
1 [platform]: collidable, resets jump, doesn't kill player
s [SPIKE]: dangerous spike, kills player. physical collision not necessary
c [COIN]: collectable coin, no physical collision
f [FLAG]: win condition flag
	has next level to load defined at the bottom of the file. e.x.:
		f "levelSelect.txt"
p [PLAYER]: spawn position for player
z# [LOAD #]: loads new level, defined at bottom of file with z# "newLevel.txt"
	level loads are stored into a vector, so start counting at 0. e.x.:
		z1 "level1.txt"
		z2 "level2.txt"
		z3 "BOSSFIGHT.txt"
		z4 "thepit.html"
LEVEL: stops loading object into world, starts level definitions
*/

class WorldLoader {

public:
	static void loadLevel(std::string levelName,	// what level to load. relative path.
		std::vector<Collidable*>& worldObjects,		// objects in world that inherit from Collidable
		std::vector<Coin>& coins,					// coins in world
		std::string& finishLoad,						// level to load when finish is reached
		std::vector<std::string>& otherLoads,		// levels to load when a load trigger is reached
		PlayerBall& player,							// player object, so coins can be reset and player position changed
		sf::RenderWindow& window,					// window object
		Camera& camera								// camera object, so camera can be adjusted to fit world
	);
};
