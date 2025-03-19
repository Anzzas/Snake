#include "game.h"

void Game::run()
{
	m_display.displayLoadingText();


	econio_sleep(GameSettings::loadingTime);


	econio_rawmode();


	while (m_isRunning)
	{
		update();


		econio_sleep(GameSettings::gameSpeed);
	}


	if (replay())
	{

		econio_clrscr();


		Game newGame{};


		newGame.run();
	}


	econio_normalmode();
}

void Game::update()
{

	m_display.render(m_snake.getBody(), m_food.getPos(), m_score);


	m_snake.move(m_controller.getDirection(m_snake.getDirection()));


	if (m_controller.isQuitReq() || checkCollision())
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
	ReplaySelection selection{ReplaySelection::playAgain};


	m_display.renderReplayMenu(m_score, InputType::up_arrow); // Do once
	
	while (true)
	{
		InputType input{ m_controller.getInput() };


		if (input == InputType::enter)
		{
			switch (selection)
			{
			case ReplaySelection::playAgain: return true;
			case ReplaySelection::changeDifficulty: continue; // Not implemented yet
			case ReplaySelection::quit: return false;
			}
		}


		else if (input == InputType::up_arrow || input == InputType::down_arrow)
		{


			switch (input)
			{
			case InputType::up_arrow:

				switch (selection)
				{
				case ReplaySelection::playAgain:
					selection = ReplaySelection::quit;
					break;


				case ReplaySelection::changeDifficulty:
					selection = ReplaySelection::playAgain;
					break;


				case ReplaySelection::quit:
					selection = ReplaySelection::changeDifficulty;
					break;
				}


				break;


			case InputType::down_arrow:

				switch (selection)
				{
				case ReplaySelection::playAgain:
					selection = ReplaySelection::changeDifficulty;
					break;


				case ReplaySelection::changeDifficulty:
					selection = ReplaySelection::quit;
					break;


				case ReplaySelection::quit:
					selection = ReplaySelection::playAgain;
					break;
				}


				break;


			default: continue;
			}


			m_display.renderReplayMenu(m_score, input);
		}
	}
}