#include "playercontroller.h"

using enum Direction;
using enum InputType;

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

std::optional<Direction> PlayerController::getMenuDirection(const InputType& input) const
{

		switch (input)
		{
		case InputType::up_arrow: return up;
		case InputType::down_arrow: return down;
		default: return {};
		}
	return {};
}

bool PlayerController::hasPressedEnter() const
{
	if (econio_kbhit())
	{
		int key{ econio_getch() };


		return key == KEY_ENTER;
	}
}


InputType PlayerController::getInput() const
{
	if (econio_kbhit())
	{
		int key{ econio_getch() };


		switch (key)
		{
		case KEY_UP: return up_arrow;
		case KEY_RIGHT: return right_arrow;
		case KEY_DOWN: return down_arrow;
		case KEY_LEFT: return left_arrow;
		case KEY_ESCAPE: return escape;
		case KEY_ENTER: return enter;
		default: return none_key;
		}
	}


	return none_key;
}