#include "display.h"

using namespace Settings;

void Display::render(const std::deque<Position>& snakeBody, const Position& food, const int& score) const
{
	auto board{ makeArray2D() };

	renderBorders(board);

	renderSnake(board, snakeBody);

	renderFood(board, food);

	renderScore(score);

	std::cout << "\n\n";

	renderBoard(board);
}

std::unique_ptr<Array2D> Display::makeArray2D() const
{
	auto board{ std::make_unique<Array2D>() };

	for (auto& row : *board)
		for (auto& col : row)
			col = ' ';

	return board;
}

void Display::renderBorders(std::unique_ptr<Array2D>& board) const
{
	for (size_t y{}; y < boardHeight; y++)
	{
		(*board.get())[y][0] = '#';
		(*board.get())[y][boardWidth - 1] = '#';

		for (size_t x{}; x < boardWidth; x++)
		{
			if (y == 0 || y == boardHeight - 1)
				(*board.get())[y][x] = '#';
		}
	}
}

void Display::renderSnake(std::unique_ptr<Array2D>& board, const std::deque<Position>& snakeBody) const
{
	for (size_t i{}; i < snakeBody.size(); i++)
	{
		if (i == 0)
			(*board.get())[snakeBody[i].y][snakeBody[i].x] = 'O';

		else
		(*board.get())[snakeBody[i].y][snakeBody[i].x] = 'o';
	}
}

void Display::renderFood(std::unique_ptr<Array2D>& board, const Position& food) const
{
	(*board.get())[food.y][food.x] = '*';
}

void Display::renderScore(const int& score) const
{
	std::cout << "Score: " << score;
}

void Display::renderBoard(const std::unique_ptr<Array2D>& board) const
{
	for (const auto& e : *board)
	{
		for (const auto& i : e)
			std::cout << i;
		std::cout << "\n";
	}
}

void Display::welcomeMsg() const
{
	std::cout << "\t\tWelcome to Snake Game !\n\n"
		<< "- Try to get the highest score possible by eating all the food !\n"
		<< "- Do not hit a wall or yourself, otherwise it is lost !\n\n";
}

void Display::gameOverMsg(const int& score) const
{
	std::cout << "\n\n\nGame over !\n"
		<< "You scored: " << score << "\n\n\n\n";
}