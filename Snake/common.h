#ifndef COMMON_H
#define COMMON_H
#include "random.h"
#include <deque>

namespace Settings
{
	constexpr int boardHeight{ 25 };
	constexpr int boardWidth{ 25 };
}

struct Position
{
	size_t y{};
	size_t x{};


	bool operator== (const Position& pos) const { return pos.x == x && pos.y == y; }


	/** Creating a random Position within the Board limits and outside the Snake's body*/
	static Position createRandomPosition(const std::deque<Position>& snakeBodyPos)
	{
		size_t y{ static_cast<size_t>(Random::get(1, Settings::boardHeight - 2)) };
		size_t x{ static_cast<size_t>(Random::get(1, Settings::boardWidth - 2)) };
		Position randomPos{ y, x };

		for (const auto& pos : snakeBodyPos)
		{
			if (randomPos == pos)
			{
				randomPos = Position::createRandomPosition(snakeBodyPos);
				continue;
			}
		}


		return randomPos;
	}
};


enum class Direction
{
	up,
	right,
	down,
	left,
	max_directions
};

#endif