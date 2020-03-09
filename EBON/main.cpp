#include "Game.h"
#include <crtdbg.h>

using uint = unsigned int;

int main()
{
	// Check for memeory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Running the game:
	Game* game = new Game();
	game->run();

	// Cleaning up the game:
	delete game;

	// Exiting application:
	return 0;
}