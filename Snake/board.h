#ifndef BOARD_H
#define BOARD_H
#include "common.h"

class Board
{
public:

	Board() = default;

	bool isEmpty(Position pos);
	bool isWall();

private:

	int width{Settings::boardWidth};
	int height{Settings:: boardHeight};
};

#endif
