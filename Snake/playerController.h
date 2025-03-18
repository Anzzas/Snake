#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "common.h"
#include <stdio.h>
#include <stdbool.h>
#include "econio.h"

class PlayerController
{
public:

	PlayerController() = default;

	Direction getDirection(Direction direction);
	const bool& isQuitReq() const;

private:

	bool m_isQuitting{};
};

#endif