#include "display.h"

using namespace Settings;

void Display::render(const std::deque<Position>& snakeBody, const Position& food, const int& score) const
{
	static bool firstFrame{ true };
	static std::deque<Position> oldSnakeBody;
	static Position oldFood{ 0, 0 };
	static int oldScore{};


	if (firstFrame)
	{
		econio_clrscr();
		renderBorders();
		renderScore(score);
		renderFood(food);
		firstFrame = false;
	}

	else
	{
		for (const auto& pos : oldSnakeBody)
		{
			econio_gotoxy(pos.x, pos.y);
			std::cout << " ";
		}

		if (oldFood != food)
		{
			econio_gotoxy(oldFood.x, oldFood.y);
			renderFood(food);
		}

		if (oldScore != score)
			renderScore(score);
	}


	renderSnake(snakeBody);

	oldSnakeBody = snakeBody;
	oldFood = food;
	oldScore = score;


	// S'assurer que tout est affiché
	econio_flush();
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
	std::cout << "\t\tWelcome to Snake Game !\n\n"
		<< "- Try to get the highest score possible by eating all the food !\n"
		<< "- Do not hit a wall or yourself, otherwise it is lost !\n\n";
}


void Display::gameOverMsg(const int& score) const
{
	econio_gotoxy(0, Settings::boardHeight + 1);


	econio_textcolor(COL_YELLOW);


	std::cout << "Game over !\n"
		<< "You scored: " << score << "\n\n\n\n";
}