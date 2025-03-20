#include "game.h"

int main()
{

	econio_rawmode();


	bool replayGame{ true };


	while (replayGame)
	{

		Game game{
			std::make_unique<Board>(),
			std::make_unique<Snake>(),
			std::make_unique<Food>(),
			std::make_unique<PlayerController>(),
			std::make_unique<Display>() };


		game.run();


		replayGame = game.replayGame();
	}
}