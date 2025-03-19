#include "game.h"

void Game::run()
{

	m_display.welcomeMsg();


	econio_sleep(GameSettings::loadingTime);


	econio_rawmode();


	while (m_isRunning)
	{
		update();
		econio_sleep(GameSettings::gameSpeed);
	}


	m_display.gameOverMsg(m_score);
	replay();


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
	econio_gotoxy(0, Settings::boardHeight + 3);
	std::cout << "Replay ?";

	econio_gotoxy(0, Settings::boardHeight + 4);
	std::cout << "Yes";

	econio_gotoxy(4, Settings::boardHeight + 4);
	std::cout << "No";
	
	return true;
}