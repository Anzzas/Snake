#include "game.h"

using enum MenuSelection;

void Game::run()
{

	if (!Menu(MenuType::main_menu))
		return;


	m_display->displayLoadingText();


	econio_sleep(GameSettings::loadingTime);


	while (m_isRunning)
	{
		update();


		econio_sleep(GameSettings::gameSpeed);
	}
}

void Game::update()
{

	m_display->render(m_snake->getBody(), m_food->getPos(), m_score);


	m_snake->move(m_controller->getDirection(m_snake->getDirection()));


	if (m_controller->isQuitReq() || checkCollision())
	{
		m_isRunning = false;
		return;
	}


	handleScore();
}

bool Game::checkCollision() const
{
	// Check wall collision
	if (m_board->isWall(m_snake->getBody()[0]))
		return true;


	// Check Snake Body Collision
	for (size_t i = 1; i < m_snake->getBody().size(); i++)
	{
		if (m_snake->getBody()[0] == m_snake->getBody()[i])
			return true;
	}


	return false;
}

void Game::handleScore()
{
	if (m_snake->getBody()[0] == m_food->getPos())
	{
		m_score += GameSettings::addScore;

		m_food->generate(Position::createRandomPosition(m_snake->getBody()));
		
		m_snake->grow();
	}
}


MenuSelection Game::getMenuSelection(MenuSelection& selection, MenuType menuType) const
{

	while (true)
	{
		InputType input{ m_controller->getInput() };


		if (input == InputType::enter)
		{
			switch (selection)
			{
			case play: return play;
			case changeDifficulty: [[fallthrough]]; // Not implemented yet
			case quit: return quit;
			}
		}


		else if (input == InputType::up_arrow || input == InputType::down_arrow)
		{


			switch (input)
			{
			case InputType::up_arrow:

				switch (selection)
				{
				case play:
					selection = quit;
					break;


				case changeDifficulty:
					selection = play;
					break;


				case quit:
					selection = changeDifficulty;
					break;
				}


				break;


			case InputType::down_arrow:

				switch (selection)
				{
				case play:
					selection = changeDifficulty;
					break;


				case changeDifficulty:
					selection = quit;
					break;


				case quit:
					selection = play;
					break;
				}


				break;


			default: continue;
			}
		}


		m_display->renderMenu(m_score, input, MenuType::replay_menu);
	}
}

bool Game::Menu(MenuType menuType) const
{

	MenuSelection selection{ play };


	m_display->renderMenu(m_score, InputType::up_arrow, menuType); // Do once for the first frame


	selection = getMenuSelection(selection, menuType);


	m_display->resetFlags();


	switch (selection)
	{
	case play: 
		econio_clrscr();
		return true;
	case changeDifficulty: [[fallthrough]]; // not implemented yet
	case quit: return false;
	}
}

bool Game::replayGame() const
{
	econio_clrscr();


	return Menu(MenuType::replay_menu);
}