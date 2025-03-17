#include "snake.h"

void Snake::move(Direction direction)
{
	Position newHeadPos{m_body.front()};

	switch (direction)
	{
	case Direction::up:
		newHeadPos.y -= 1;
		break;
	case Direction::right:
		newHeadPos.x += 1;
		break;
	case Direction::down:
		newHeadPos.y += 1;
		break;
	case Direction::left:
		newHeadPos.x -= 1;
		break;
	}

	for (size_t i = m_body.size() - 1; i > 0; i--)
		m_body[i] = m_body[i - 1];

	m_body[0] = newHeadPos;
}