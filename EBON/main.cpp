/*=============================================================================
 * Project:     EBON Engine
 * Version:     1.0
 *
 * Class:       main.cpp
 * Purpose:     To hold the entry point of the program, and to start the game.
 *
 * Author:      Lachlan Wernert
 *===========================================================================*/
#include "Game.h"
#include <crtdbg.h>

using uint = unsigned int;

int main()
{
	// Check for memeory leaks.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Running the game:
	Game* game = new Game();
	game->Run();

	// Cleaning up the game:
	delete game;

	// Exiting application:
	return 0;
}