#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "common.h"
#include <stdio.h>
#include <stdbool.h>
#include "econio.h"

/** Keyboard control manager*/
class PlayerController
{
public:

	PlayerController() = default;

	
	/** Converting inputs (arrow keys) into a Direction*/
	Direction getDirection(Direction direction);


	/** Detecting ESCAPE input and stop the game if pressed*/
	const bool& isQuitReq() const;

private:

	bool m_isQuitting{};
};

#endif