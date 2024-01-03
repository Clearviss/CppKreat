#include <iostream>
#include "Game.h"

int main()
{
	//making random manually because cpp is weird
	std::srand(static_cast<unsigned>(time(NULL)));

	//init Game
	Game game;

	// Main loop
	while (game.getWindowIsOpen())
	{
		
		//Update Frames
		game.update();
		//Render Frames
		game.render();
	}

	

	return 0;
}
