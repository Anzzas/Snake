#ifndef FOOD_H
#define FOOD_H
#include "random.h"

class Food
{
public:

	static Food generate(Position position) { return Food{ position }; }
	const Position& getPos() const { return m_pos; }

private:

	Food(Position pos)
		: m_pos{ pos }
	{
	}

	Position m_pos{};
};

#endif