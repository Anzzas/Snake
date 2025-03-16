#ifndef SNAKE_H
#define SNAKE_H
#include "common.h"

class Snake
{
public:

	void move(Direction direction);
	void grow();

private:

	Direction m_direction{};
};

#endif