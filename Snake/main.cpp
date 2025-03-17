#include "game.h"
#include <iostream>

int main()
{
	std::cout << "\t\tWelcome to Snake Game !\n\n"
		<< "- Try to get the highest score possible by eating all the food !\n"
		<< "- Do not hit a wall or yourself, otherwise it is lost !\n\n";

	Game game{};
	Display display{};
	display.render();
}