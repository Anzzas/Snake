#ifndef SNAKE_H
#define SNAKE_H
#include "common.h"
#include <deque>

class Snake
{
public:

	void move(Direction direction);
	void grow();

private:

	std::deque<Position> m_body{
	Position{0, 0},
	Position{0, 1},
	Position{0, 2},
	Position{0, 3},
	};

	Direction m_direction{};
};

#endif