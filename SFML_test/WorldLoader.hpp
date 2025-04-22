#include <SFML/Graphics.hpp>
#include "Collidable.hpp"
#include "PlayerBall.hpp"
#include "Camera.hpp"

/*
What the characters mean in a level file:

l [LEFT EDGE]: clamp camera from moving past that left
r [RIGHT EDGE]: clamp camera from movign past that right
0 [AIR]: no block here
1 [GROUND]: filler for world, has collisions but no special properties
2 [FLOOR]: has collision, allows player to reset jump here
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
*/

class WorldLoader {
	static void loadLevel(std::vector<Collidable>& worldObjects, PlayerBall& player, sf::RenderWindow& window, Camera& camera) {

	}


};