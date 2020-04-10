#include <iostream>
#include <cstdlib>
#include <thread>
#include <atomic>

#include <conio.h>
#include <windows.h>

#include "Board.h"

using namespace std;

// Key index for safe transfer between threads
std::atomic_int keyPressed = 0;

// Waiting for the user to press a key
void input(std::atomic_int &keyPressed)
{
	while (keyPressed != 120) // Key "x" for exit
	{
		if (_kbhit()) { // User presed key
			keyPressed = _getch(); // Get key index
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Sleep thread
	}
}

int main()
{
	// Resize console window
	system("MODE CON: COLS=100 LINES=50");

	std::thread inputThread(input, std::ref(keyPressed)); // Thread for tracking user actions
	inputThread.detach(); // Detach the thread

	Board board; // Game board
	std::thread boardThread(board, std::ref(keyPressed)); // Thread for Game board
	boardThread.join(); // Waiting for the completion of the thread
}