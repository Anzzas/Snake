#include "display.h"

using namespace Settings;

void Display::render(const std::deque<Position>& snakeBody, const Position& food, const int& score) const
{
	static bool firstFrame{ true };


	if (firstFrame)
	{
		renderFirstFrame(food, score);
		removeOldFrame(snakeBody, food, score);
		firstFrame = false;
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


void Display::gameOverMsg(const int& score) const
{
	econio_gotoxy(0, Settings::boardHeight + 1);


	econio_textcolor(COL_YELLOW);


	std::cout << "Game over !\n"
		<< "You scored: " << score << "\n\n\n\n";
}


void Display::renderReplayMenu(const int& score) const
{
	constexpr std::array<int, 3> rows{ 2, 6, 20 };
	constexpr std::array<int, 2> cols{ 40, 65 };
	constexpr int width{ cols[1] - cols[0] };
	constexpr int centerX{ cols[0] + width / 2 };


	econio_clrscr();


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


	econio_textcolor(COL_YELLOW);
	std::string gameOverText = "GAME OVER!";
	econio_gotoxy(centerX - gameOverText.length() / 2, 4);
	std::cout << gameOverText;


	std::string scorePrefix = "Final score: ";
	std::string scoreText = scorePrefix + std::to_string(score);
	econio_gotoxy(centerX - scoreText.length() / 2, 5);
	std::cout << scoreText;


	econio_textcolor(COL_WHITE);
	std::string option1 = "Play Again";
	econio_gotoxy(centerX - option1.length() / 2, 10);
	std::cout << option1;


	std::string option2 = "Change Difficulty";
	econio_gotoxy(centerX - option2.length() / 2, 12);
	std::cout << option2;


	std::string option3 = "Quit";
	econio_gotoxy(centerX - option3.length() / 2, 14);
	std::cout << option3;


	econio_textcolor(COL_LIGHTGRAY);
	std::string instruction1 = "[UP/DOWN]: Navigate";
	econio_gotoxy(centerX - instruction1.length() / 2, 17);
	std::cout << instruction1;


	std::string instruction2 = "[ENTER]: Select";
	econio_gotoxy(centerX - instruction2.length() / 2, 18);
	std::cout << instruction2;


	econio_flush();


	econio_gotoxy(0, 22); // For end program text
}