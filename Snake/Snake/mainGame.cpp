#include <iostream>
#include <cstdlib>
#include <thread>
#include <atomic>

#include <conio.h>
#include <windows.h>

#include "Board.h"

using namespace std;

// Безопасная межпотоковая переменная отвечающая за индекс нажатой пользователем клавиши
std::atomic_int keyPressed = 0;

// Функция слежения за нажатиями пользователем клавиш
void input(std::atomic_int &keyPressed)
{
	while (keyPressed != 120) // В случае нажатия "x" завершаем работу
	{
		if (_kbhit()) { // Системное событие нажатия пользователем клавиши
			keyPressed = _getch(); // Получаем индекс нажатой пользователем клавиши
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10)); // Усыпляем текущий поток на 10 миллисекунд
	}
}

int main()
{
	// Настройки окна консоли.
	system("MODE CON: COLS=100 LINES=50");

	// Отслеживаем нажатие клавишь пользователем в отдельном потоке.
	std::thread inputThread(input, std::ref(keyPressed));
	inputThread.detach(); // Отпускаем поток в свободное плавание

	// Объект игровой доски отправляем в отдельный поток и ждём пока он завершится.
	Board board;
	std::thread boardThread(board, std::ref(keyPressed));
	boardThread.join(); // Ждём завершения работы потока
}