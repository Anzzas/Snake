#include "game.h"

void Game::run()
{
	bool replayGame{ true };


	m_display.welcomeMsg();


	while (replayGame)
	{
		econio_sleep(GameSettings::loadingTime);


		econio_rawmode();


		while (m_isRunning)
		{
			update();
			econio_sleep(GameSettings::gameSpeed);
		}


		m_display.gameOverMsg(m_score);


		replayGame = replay();
		m_isRunning = replayGame;
	}


	econio_normalmode();
}

void Game::update()
{

	m_display.render(m_snake.getBody(), m_food.getPos(), m_score);


	m_snake.move(m_controller.getDirection(m_snake.getDirection()));


	if (m_controller.isQuitReq())
	{
		m_isRunning = false;
		return;
	}

	if (checkCollision())
	{
		m_isRunning = false;
		return;
	}


	handleScore();
}

bool Game::checkCollision() const
{
	// Check wall collision
	if (m_board.isWall(m_snake.getBody()[0]))
		return true;


	// Check Snake Body Collision
	for (size_t i = 1; i < m_snake.getBody().size(); i++)
	{
		if (m_snake.getBody()[0] == m_snake.getBody()[i])
			return true;
	}


	return false;
}

void Game::handleScore()
{
	if (m_snake.getBody()[0] == m_food.getPos())
	{
		m_score += GameSettings::addScore;

		m_food.generate(Position::createRandomPosition(m_snake.getBody()));
		
		m_snake.grow();
	}
}

bool Game::replay() const
{
	constexpr Position replayPos{Settings::boardHeight + 5, 0 };
	constexpr Position yesPos{Settings::boardHeight + 5, 0 };
	constexpr Position noPos{ Settings::boardHeight + 5, 5 };

	econio_gotoxy(replayPos.x, replayPos.y);
	std::cout << "Replay ?";

	econio_gotoxy(yesPos.x, yesPos.y);
	std::cout << "Yes";

	econio_gotoxy(noPos.x, noPos.y);
	std::cout << "No";
	
	Direction currentDir{ Direction::left };
	econio_gotoxy(yesPos.x, yesPos.y + 1);
	while (true)
	{
		if (econio_kbhit())
		{
			const int key{ econio_getch() };

			switch (key)
			{
			case KEY_ENTER: return currentDir == Direction::left ? true : false;


			case KEY_LEFT:
				currentDir = Direction::left;
				econio_gotoxy(yesPos.x, yesPos.y + 1);
				break;


			case KEY_RIGHT:
				currentDir = Direction::right;
				econio_gotoxy(noPos.x, noPos.y + 1);
				break;

				
			default: continue;
			}

		}
	}
	return true;
}