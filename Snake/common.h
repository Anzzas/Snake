#ifndef COMMON_H
#define COMMON_H

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