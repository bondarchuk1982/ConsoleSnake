#pragma once
#include <iostream>
#include <cstdlib>
#include <thread>
#include <atomic>

#include <conio.h>

#include "Food.h"
#include "Snake.h"

class Board
{
public:
	Board();

	// Overload the operator to call the function "Run" at the start of the thread
	void operator()(std::atomic_int &keyPressed)
	{
		run(keyPressed);
	}
	void run(std::atomic_int &keyPressed);

private:
	void logic(); // Business logic games
	void demo(); // Demo mode
	void drawBoard(); // Draw a board in the console
	void drawGameStatus(); // Draw the game status in the console
	void menu(); // Draw a menu in the console
	void restartGame(); // Reset object parameters to initial
	void moveSnake(); // Move the body of the snake on the board
	void autoMove(); // Automatic movement of the body of a snake on a board
	void checkGameOver(); // Check the conditions for ending the game
	void checkFood(); // Check the coordinates for the presence of the object food
	void keyPressedToGameStatus(std::atomic_int &keyPressed); // Check the user-pressed key for the corresponding game status
	void keyPressedToMovement(const std::atomic_int &keyPressed); // Check the key pressed by the user for the corresponding direction of movement of the snake

	bool checkWalls(); // Checking the boundaries of the board

	const int m_width = 40; // Default board width
	const int m_height = 30; // Default board height

	const int m_defaultDelay = 250; // Default board update delay
	int m_totalDelay = m_defaultDelay; // Total board update delay and game speed
	int m_score = 0; // Total score

	Food m_food; // Class Food
	Snake m_snake; // Class Snake
};

