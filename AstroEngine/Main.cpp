#include "Game.h"
#include "SFML/System.hpp"

int main()
{
	Game game;
	while (!game.GetWindow()->IsDone())
	{
		game.Run();
	}
}