#include <iostream>

#include "Game.h"

int main()
{
	try {
		Game game(3);
		game.runGame();
	}
	catch (...) {
		std::cout << "unkown mistake accured\n";
	}
	return 0;
}
