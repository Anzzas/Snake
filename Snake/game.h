#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "snake.h"
#include "food.h"
#include "playerController.h"
#include "display.h"

class Game
{
public:

	Game() = default;

	void run();
	void update();
	bool checkCollision();
	void handleScore();

private:

	Board m_board{};
	Snake m_snake{};
	Food m_food{Food::generate(Position::createRandomPosition())};
	PlayerController m_controller{};
	Display m_display{};
	int m_score{};
	bool m_isRunning{};
};

#endif