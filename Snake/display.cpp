﻿#include "display.h"

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


void Display::renderMenu(const int& score, const InputType& input, MenuType menuType) const
{

	if (m_firstMenuFrame)
	{
		econio_clrscr();


		renderReplayMenuBorders();


		renderReplayMenuText(score, menuType);


		m_firstMenuFrame = false;
	}


	renderMenuSelectCursor(input);


	econio_flush();


	econio_gotoxy(0, 22); // For end program text only
}


void Display::renderReplayMenuBorders() const
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

void Display::renderReplayMenuText(const int& score, MenuType menuType) const
{
	econio_textcolor(COL_YELLOW);
	std::string gameOverText{ menuType == MenuType::replay_menu ? "GAME OVER!" : "SNAKE" };
	econio_gotoxy(centerX - gameOverText.length() / 2, 4);
	std::cout << gameOverText;


	std::string scorePrefix{ menuType == MenuType::replay_menu ? "Final score: " : " " };
	std::string scoreText{ menuType == MenuType::replay_menu ? scorePrefix + std::to_string(score) : " " };
	econio_gotoxy(centerX - scoreText.length() / 2, 5);
	std::cout << scoreText;


	econio_textcolor(COL_WHITE);
	std::string option1{ menuType == MenuType::replay_menu ? "Play Again" : "Play" };
	econio_gotoxy(centerX - option1.length() / 2, 10);
	std::cout << option1;


	std::string option2{ "Change Difficulty" };
	econio_gotoxy(centerX - option2.length() / 2, 12);
	std::cout << option2;


	std::string option3{ "Quit" };
	econio_gotoxy(centerX - option3.length() / 2, 14);
	std::cout << option3;


	econio_textcolor(COL_LIGHTGRAY);
	std::string instruction1{ "[UP/DOWN]: Navigate" };
	econio_gotoxy(centerX - instruction1.length() / 2, 17);
	std::cout << instruction1;


	std::string instruction2{ "[ENTER]: Select" };
	econio_gotoxy(centerX - instruction2.length() / 2, 18);
	std::cout << instruction2;
}


void Display::renderMenuSelectCursor(const InputType& input) const
{
	
	if (input == InputType::up_arrow || input == InputType::down_arrow)
	{
		econio_gotoxy(m_currentCursorPos.x, m_currentCursorPos.y);
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


		econio_gotoxy(m_currentCursorPos.x, m_currentCursorPos.y);
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