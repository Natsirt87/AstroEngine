#include "Game.h"
#include "SFML/System.hpp"

int main()
{
	Game* game = new Game();
	while (!game->GetWindow()->IsDone())
	{
		game->Run();
	}
	delete game;
}