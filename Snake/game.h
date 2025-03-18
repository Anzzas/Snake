#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "snake.h"
#include "food.h"
#include "playerController.h"
#include "display.h"
#include "econio.h"

class Game
{
public:

	Game() = default;

	void run();

private:

	Board m_board{};
	Snake m_snake{};
	Food m_food{Food::generate(Position::createRandomPosition())};
	PlayerController m_controller{};
	Display m_display{};
	int m_score{};
	bool m_isRunning{};

	void update();
	bool checkCollision() const;
	void handleScore();
};

#endif