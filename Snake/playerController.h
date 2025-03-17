#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H
#include "common.h"

class PlayerController
{
public:

	Direction getDirection();
	bool isQuitReq();
};

#endif