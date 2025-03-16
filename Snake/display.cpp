#include "display.h"

using namespace Settings;

void Display::render() const
{
	auto board{ makeArray2D() };

	renderBorders(board);

	renderSnake(board);

	for (const auto& e : *board)
	{
		for (const auto& i : e)
			std::cout << i;
		std::cout << "\n";
	}
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

void Display::renderSnake(std::unique_ptr<Array2D>& board) const
{

}