#ifndef DISPLAY_H
#define DISPLAY_H
#include "common.h"
#include <array>
#include <memory>
#include <iostream>

using Array2D = std::array<std::array<char, Settings::boardWidth>, Settings::boardHeight>;

class Display
{
public:

	const int& showScore();
	void render() const;

private:

	std::unique_ptr<Array2D> makeArray2D() const;
	void renderBorders(std::unique_ptr<Array2D>& board) const;
	void renderSnake(std::unique_ptr<Array2D>& board) const;
};

#endif