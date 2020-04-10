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
	// Перегружаем оператор () чтобы при старте потока запустить стартовую функцию "run"
	void operator()(std::atomic_int &keyPressed)
	{
		run(keyPressed);
	}
	void run(std::atomic_int &keyPressed);

private:
	// Функции внутренней бизнеслогики
	void logic();
	void demo();
	void drawBoard();
	void drawGameStatus();
	void menu();
	void restartGame();
	void moveSnake();
	void autoMove();
	void checkGameOver();
	void checkFood();
	void keyPressedToGameStatus(std::atomic_int &keyPressed);
	void keyPressedToMovement(const std::atomic_int &keyPressed);

	bool checkWalls();

	// Мемберы:
	// Параметры игровой доски
	const int m_width = 40;
	const int m_height = 30;
	// Текущий счёт
	int m_score = 0;
	// Частота перерисовки игрового поля и соответственно скорость игры
	const int m_defaultDelay = 250;
	int m_totalDelay = m_defaultDelay;

	// Объект еды
	Food m_food;
	// Объект змейки
	Snake m_snake;
};

