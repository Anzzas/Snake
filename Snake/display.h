#ifndef DISPLAY_H
#define DISPLAY_H
#include "common.h"
#include "econio.h"
#include <iostream>
#include <deque>
#include <array>

namespace ReplayMenuSettings
{
	constexpr std::array<int, 3> rows{ 2, 6, 20 };
	constexpr std::array<int, 2> cols{ 40, 65 };
	constexpr int width{ cols[1] - cols[0] };
	constexpr int centerX{ cols[0] + width / 2 };
	constexpr Position playAgainCursorPos{ 10, centerX - 7 };
	constexpr Position difficultyCursorPos{ 12, centerX - 10 };
	constexpr Position quitCursorPos{ 14, centerX - 4 };
}


//* Class in charge of displaying everything
class Display
{
public:

	/** Displaying the first message as the program starts*/
	void welcomeMsg() const;


	/** Displaying all the objects (Snake, Food, Score and the Borders*/
	void render(const std::deque<Position>& snakeBody, const Position& food, const int& score) const;


	/** Displaying once the Replay Menu and the select Cursor in real time*/
	void renderReplayMenu(const int& score, const InputType& input) const;


	void displayLoadingText() const;

private:

	/** State for the first Frame only during the game*/
	mutable bool m_firstMainGameFrame{ true };


	/** State for the first frame only for the replay menu*/
	mutable bool m_firstReplayMenuFrame{ true };


	/** Position state to keep in memory the select Cursor position*/
	mutable Position m_currentCursorPos{ ReplayMenuSettings::difficultyCursorPos };


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


	void renderReplayMenuBorders() const;


	void renderReplayMenuText(const int& score) const;


	void renderReplayMenuSelectCursor(const InputType& input) const;
};

#endif