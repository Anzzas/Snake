#include "game.h"

void Game::run()
{

	m_display.welcomeMsg();
	econio_rawmode();

	while (!m_controller.isQuitReq())
	{
		update();
		econio_sleep(0.1);
	}

	m_display.gameOverMsg(m_score);
	econio_normalmode();
}

void Game::update()
{


	m_display.render(m_snake.getBody(), m_food.getPos(), m_score);


	m_snake.move(m_controller.getDirection(m_snake.getDirection()));


	checkCollision();


	handleScore();
}

bool Game::checkCollision() const
{

}

void Game::handleScore()
{

}