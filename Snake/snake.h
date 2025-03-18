#ifndef SNAKE_H
#define SNAKE_H
#include "common.h"
#include <deque>

class Snake
{
public:

	Snake() = default;

	void move(Direction direction);
	void grow();
	const std::deque<Position>& getBody() const { return m_body; }
	const Direction& getDirection() const { return m_direction; }

private:

	std::deque<Position> m_body{
	Position{12, 4},
	Position{12, 3},
	Position{12, 2},
	Position{12, 1},
	};

	Direction m_direction{Direction::right};
};

#endif