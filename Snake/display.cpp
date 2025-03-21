#include "display.h"

using namespace Settings;
using namespace MenuSettings;

void Display::render(const std::deque<Position>& snakeBody, const Position& food, const int& score) const
{


	if (m_firstMainGameFrame)
	{
		renderFirstFrame(food, score);
		removeOldFrame(snakeBody, food, score);
		m_firstMainGameFrame = false;
	}


	else
		removeOldFrame(snakeBody, food, score);


	renderSnake(snakeBody);


	econio_flush();
}


void Display::renderFirstFrame(const Position& food, const int& score) const
{
	econio_clrscr();
	renderBorders();
	renderScore(score);
	renderFood(food);
}


void Display::removeOldFrame(const std::deque<Position>& snakeBody, const Position& food, const int& score) const
{
	static std::deque<Position> oldSnakeBody{};
	static Position oldFood{ 0, 0 };
	static int oldScore{};

	for (const auto& pos : oldSnakeBody)
	{
		econio_gotoxy(static_cast<int>(pos.x), static_cast<int>(pos.y));
		std::cout << " ";
	}

	if (oldFood != food)
		renderFood(food);


	if (oldScore != score)
		renderScore(score);


	oldSnakeBody = snakeBody;
	oldFood = food;
	oldScore = score;
}


void Display::renderBorders() const
{
	econio_textcolor(COL_YELLOW);
	for (int y{}; y < boardHeight; y++)
	{
		for (int x{}; x < boardWidth; x++)
		{
			if (x == 0 || x == boardWidth - 1 || y == 0 || y == boardHeight - 1)
			{
				econio_gotoxy(x, y);
				std::cout << "#";
			}
		}
	}
}


void Display::renderSnake(const std::deque<Position>& snakeBody) const
{
	for (size_t i{}; i < snakeBody.size(); i++)
	{
		const auto& [snakeBodyY, snakeBodyX] = snakeBody[i];


		econio_gotoxy(static_cast<int>(snakeBodyX), static_cast<int>(snakeBodyY));


		if (i == 0)
		{
			econio_textcolor(COL_LIGHTGREEN);
			std::cout << "O";
		}


		else
		{
			econio_textcolor(COL_GREEN);
			std::cout << "o";
		}
	}
}


void Display::renderFood(const Position& food) const
{
	econio_gotoxy(static_cast<int>(food.x), static_cast<int>(food.y));
	

	econio_textcolor(COL_LIGHTRED);


	std::cout << "*";
}


void Display::renderScore(const int& score) const
{
	econio_textcolor(COL_YELLOW);


	econio_gotoxy(0, Settings::boardHeight + 1);


	std::cout << "Score: " << score;
}


void Display::welcomeMsg() const
{
	econio_textcolor(COL_YELLOW);


	std::cout << "\t\tWelcome to Snake Game !\n\n"
		<< "- Try to get the highest score possible by eating all the food !\n"
		<< "- Do not hit a wall or yourself, otherwise it is lost !\n\n";
}


void Display::renderMenu(const int& score, const InputType& input, MenuType menuType, const DifficultyMode& difficulty) const
{

	if (m_firstMenuFrame)
	{
		econio_clrscr();


		renderMenuBorders();


		renderMenuText(score, menuType, difficulty);


		m_firstMenuFrame = false;
	}


	renderMenuSelectCursor(input);


	econio_flush();


	econio_gotoxy(0, 22); // For end program text only
}


void Display::renderMenuBorders() const
{
	for (const auto& y : rows)
	{
		for (int x = cols.front(); x < cols.back() + 1; x++)
		{
			econio_gotoxy(x, y);
			if (x == cols.front() || x == cols.back())
				std::cout << "+";
			else
				std::cout << "-";
		}
	}


	for (const auto& x : cols)
	{
		for (int y = rows.front() + 1; y < rows.back(); y++)
		{
			econio_gotoxy(x, y);

			if (std::find(rows.begin(), rows.end(), y) != rows.end())
				continue;
			else
				std::cout << "|";
		}
	}
}

void Display::renderMenuText(const int& score, MenuType menuType, const DifficultyMode& difficulty) const
{
	econio_textcolor(COL_YELLOW);
	std::string titleText{};
	switch (menuType)
	{
	case MenuType::main_menu:
		titleText = "SNAKE";
		break;
	case MenuType::replay_menu:
		titleText = "GAME OVER!";
		break;
	case MenuType::difficulty_menu:
		titleText = "CHOOSE DIFFICULTY";
		break;
	}
	econio_gotoxy(centerX - static_cast<int>(titleText.length()) / 2, 4);
	std::cout << titleText;


	std::string text2Prefix{};
	switch (menuType)
	{
	case MenuType::main_menu:
		text2Prefix = " ";
		break;
	case MenuType::replay_menu:
		text2Prefix = "Final score: ";
		break;
	case MenuType::difficulty_menu:
		text2Prefix = "Current: ";
		break;
	}

	std::string text2{};
	switch (menuType)
	{
	case MenuType::main_menu:
		text2 = " ";
		break;

	case MenuType::replay_menu:
		text2 = text2Prefix + std::to_string(score);
		break;

	case MenuType::difficulty_menu:
		switch (difficulty)
		{
		case DifficultyMode::easy: text2 = text2Prefix + "easy";
			break;
		case DifficultyMode::medium: text2 = text2Prefix + "medium";
			break;
		case DifficultyMode::hard: text2 = text2Prefix + "hard";
		}
	}
	econio_gotoxy(centerX - static_cast<int>(text2Prefix.length()) / 2, 5);
	std::cout << text2;


	econio_textcolor(COL_WHITE);
	std::string option1{};
	switch (menuType)
	{
	case MenuType::main_menu:
		option1 = "Play";
		break;
	case MenuType::replay_menu:
		option1 = "Play again";
		break;
	case MenuType::difficulty_menu:
		option1 = "Easy";
		break;
	}
	econio_gotoxy(centerX - static_cast<int>(option1.length()) / 2, 10);
	std::cout << option1;


	std::string option2{menuType == MenuType::difficulty_menu ? "Medium" : "Change Difficulty"};
	econio_gotoxy(centerX - static_cast<int>(option2.length()) / 2, 12);
	std::cout << option2;


	std::string option3{menuType == MenuType::difficulty_menu ? "Hard" : "Quit"};
	econio_gotoxy(centerX - static_cast<int>(option3.length()) / 2, 14);
	std::cout << option3;


	econio_textcolor(COL_LIGHTGRAY);
	std::string instruction1{ "[UP/DOWN]: Navigate" };
	econio_gotoxy(centerX - static_cast<int>(instruction1.length()) / 2, 17);
	std::cout << instruction1;


	std::string instruction2{ "[ENTER]: Select" };
	econio_gotoxy(centerX - static_cast<int>(instruction2.length()) / 2, 18);
	std::cout << instruction2;
}


void Display::renderMenuSelectCursor(const InputType& input) const
{
	
	if (input == InputType::up_arrow || input == InputType::down_arrow)
	{
		econio_gotoxy(static_cast<int>(m_currentCursorPos.x), static_cast<int>(m_currentCursorPos.y));
		std::cout << " ";


		switch (input)
		{
		case InputType::up_arrow:

			if (m_currentCursorPos == playAgainCursorPos)
				m_currentCursorPos = quitCursorPos;


			else if (m_currentCursorPos == difficultyCursorPos)
				m_currentCursorPos = playAgainCursorPos;


			else if (m_currentCursorPos == quitCursorPos)
				m_currentCursorPos = difficultyCursorPos;


			break;


		case InputType::down_arrow:

			if (m_currentCursorPos == playAgainCursorPos)
				m_currentCursorPos = difficultyCursorPos;


			else if (m_currentCursorPos == difficultyCursorPos)
				m_currentCursorPos = quitCursorPos;


			else if (m_currentCursorPos == quitCursorPos)
				m_currentCursorPos = playAgainCursorPos;
		}


		econio_gotoxy(static_cast<int>(m_currentCursorPos.x), static_cast<int>(m_currentCursorPos.y));
		std::cout << ">";
	}
}


void Display::displayLoadingText() const
{
	econio_textcolor(COL_LIGHTGRAY);
	econio_gotoxy(50, 15);
	std::cout << "Loading ...";
}


void Display::resetFlags()
{
	m_firstMainGameFrame = true;
	m_firstMenuFrame = true;
	m_currentCursorPos = MenuSettings::difficultyCursorPos;
}