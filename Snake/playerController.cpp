#include "playercontroller.h"

using enum Direction;

/** Getting the input direction
* Returns the current direction if an opposite direction key is pressed
* Manage ESCAPE key case if the player wants to quit the game
*/
Direction PlayerController::getDirection(Direction currentDirection)
{
	if (econio_kbhit())
	{
		int key = econio_getch();

		switch (key)
		{
		case KEY_UP:
			if (currentDirection != down)
				return up;
			break;
		case KEY_RIGHT:
			if (currentDirection != left)
				return right;
			break;
		case KEY_DOWN:
			if (currentDirection != up)
				return down;
			break;
		case KEY_LEFT:
			if (currentDirection != right)
				return left;
			break;
		case KEY_ESCAPE: 
			m_isQuitting = true;
			[[fallthrough]];
		default: return currentDirection;
		}
	}


	return currentDirection;
}

//* Returns whether the player has pressed ESCAPE key to QUIT or not
const bool& PlayerController::isQuitReq() const
{
	return m_isQuitting;
}

Direction PlayerController::getMenuDirection(const Direction& currentDirection) const
{
	if (econio_kbhit())
	{
		int key{ econio_getch() };

		switch (key)
		{
		case KEY_LEFT: return left;
		case KEY_RIGHT: return right;
		default: return currentDirection;
		}
	}
	return currentDirection;
}

bool PlayerController::hasPressedEnter() const
{
	if (econio_kbhit())
	{
		int key{ econio_getch() };


		return key == KEY_ENTER;
	}
}