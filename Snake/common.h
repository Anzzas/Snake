#ifndef COMMON_H
#define COMMON_H
#include "random.h"

namespace Settings
{
	constexpr int boardHeight{ 25 };
	constexpr int boardWidth{ 120 };
}

struct Position
{
	size_t y{};
	size_t x{};

	bool operator== (const Position& pos) { return pos.x == x && pos.y == y; }

	static Position createRandomPosition()
	{
		size_t y{ static_cast<size_t>(Random::get(1, Settings::boardHeight - 1)) };
		size_t x{ static_cast<size_t>(Random::get(1, Settings::boardWidth - 1)) };
		Position randomPos{ y, x };

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