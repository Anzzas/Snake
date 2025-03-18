#include "game.h"

void Game::run()
{

	m_display.welcomeMsg();
	econio_rawmode();


	while (m_isRunning)
	{
		update();
		econio_sleep(0.01);
	}


	m_display.gameOverMsg(m_score);


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
		m_score += 50;
		m_food.generate(Position::createRandomPosition());
		m_snake.grow();
	}
}