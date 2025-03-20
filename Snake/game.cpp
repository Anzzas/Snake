#include "game.h"

using enum MenuSelection;

void Game::run()
{
	econio_rawmode();


	if (!Menu(MenuType::main_menu))
		return;


	m_display.displayLoadingText();


	econio_sleep(GameSettings::loadingTime);


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
	MenuSelection selection{ play };


	m_display.renderMenu(m_score, InputType::up_arrow, MenuType::replay_menu); // Do once for the first frame
	

	selection = getMenuSelection(selection, MenuType::replay_menu);


	switch (selection)
	{
	case play: return true;
	case changeDifficulty: [[fallthrough]]; // not implemented yet
	case quit: return false;
	}
}


MenuSelection Game::getMenuSelection(MenuSelection& selection, MenuType menuType) const
{

	while (true)
	{
		InputType input{ m_controller.getInput() };


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


		m_display.renderMenu(m_score, input, MenuType::replay_menu);
	}
}

bool Game::Menu(MenuType menuType)
{

	MenuSelection selection{ play };


	m_display.renderMenu(m_score, InputType::up_arrow, menuType); // Do once for the first frame


	selection = getMenuSelection(selection, menuType);


	m_display.resetFlags();


	switch (selection)
	{
	case play: 
		econio_clrscr();
		return true;
	case changeDifficulty: [[fallthrough]]; // not implemented yet
	case quit: return false;
	}
}