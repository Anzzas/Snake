#ifndef DISPLAY_H
#define DISPLAY_H
#include "common.h"
#include "econio.h"
#include <iostream>
#include <deque>


//* Class in charge of displaying everything
class Display
{
public:

	/** Displaying the first message as the program starts*/
	void welcomeMsg() const;


	/** Displaying the Game Over message and the final Score when the player lose*/
	void gameOverMsg(const int& score) const;


	/** Displaying all the objects (Snake, Food, Score and the Borders*/
	void render(const std::deque<Position>& snakeBody, const Position& food, const int& score) const;

private:

	/** Rendering the borders of the game*/
	void renderBorders() const;


	/** Rendering the Snake body parts*/
	void renderSnake(const std::deque<Position>& snakeBody) const;


	/** Rendering the food (*)*/
	void renderFood(const Position& food) const;


	/** Rendering the player's score*/
	void renderScore(const int& score) const;


	/*
	* Rendering the first frame only
	* Used to prevent flickerings and having to render things like borders or other things that are not moving on a frame
	*/
	void renderFirstFrame(const Position& food, const int& score) const;


	/** This removes a specific object that moved since the console is not cleared every frame
	* The snake is updated every frame
	* The Food is only updated when moved
	* The Score is only updated when it goes up
	*/
	void removeOldFrame(const std::deque<Position>& snakeBody, const Position& food, const int& score) const;
};

#endif