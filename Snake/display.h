#ifndef DISPLAY_H
#define DISPLAY_H
#include "common.h"
#include "econio.h"
#include <array>
#include <memory>
#include <iostream>
#include <deque>

using Array2D = std::array<std::array<char, Settings::boardWidth>, Settings::boardHeight>;

//* Class in charge of displaying everything
class Display
{
public:

	void welcomeMsg() const;
	void gameOverMsg(const int& score) const;
	const int& showScore() const;
	void render(const std::deque<Position>& snakeBody, const Position& food, const int& score) const;

private:

	void renderBorders() const;
	void renderSnake(const std::deque<Position>& snakeBody) const;
	void renderFood(const Position& food) const;
	void renderScore(const int& score) const;
};

#endif