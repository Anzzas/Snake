#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "snake.h"
#include "food.h"
#include "playerController.h"
#include "display.h"
#include "econio.h"

namespace GameSettings
{
	constexpr int addScore{ 50 };
	constexpr double gameSpeed{ 0.05 };
	constexpr double loadingTime{ 1.5 };
}

class Game
{
public:

	Game() = default;


	/** Main Game function where everything runs*/
	void run();

private:

	Board m_board{};
	Snake m_snake{};
	Food m_food{Position::createRandomPosition(m_snake.getBody())};
	PlayerController m_controller{};
	Display m_display{};
	int m_score{};
	bool m_isRunning{ true };


	/** Loop where everythings in updated every frame (Render, Score, objects Positions)*/
	void update();


	/** Collision CHECK for BORDERS and Snake's BODY*/
	bool checkCollision() const;


	/** Score handling
	* Detecting whether the Snake's head has the same Position as the Food (collision)
	* Then add points to the score
	* Then generating a new Position for the food 
	* And growing the Snake body by ONE */
	void handleScore();


	/** Return bool whether the player wants to replay the game or not*/
	bool replay() const;
};

#endif