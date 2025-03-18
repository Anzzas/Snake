#ifndef FOOD_H
#define FOOD_H
#include "random.h"

class Food
{
public:

	Food(Position pos)
		: m_pos{ pos }
	{
	}

	void generate(Position position) { m_pos = position; }
	const Position& getPos() const { return m_pos; }

private:

	Position m_pos{};
};

#endif