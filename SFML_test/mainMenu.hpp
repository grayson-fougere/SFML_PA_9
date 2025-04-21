#pragma once

#include <memory>
#include <SFML/Graphics/Text.hpp>
#include <iostream>


class mainMenu
{
public:
	mainMenu();
	~mainMenu();



private:

	sf::Text gameTitle;
	bool menuOpen = true;

};



//mainMenu::mainMenu() {
//
//	gameTitle.setString("Red Ball");
//
//}


