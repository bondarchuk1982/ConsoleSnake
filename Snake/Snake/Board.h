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
	// ����������� �������� () ����� ��� ������ ������ ��������� ��������� ������� "run"
	void operator()(std::atomic_int &keyPressed)
	{
		run(keyPressed);
	}
	void run(std::atomic_int &keyPressed);

private:
	// ������� ���������� ������������
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

	// �������:
	// ��������� ������� �����
	const int m_width = 40;
	const int m_height = 30;
	// ������� ����
	int m_score = 0;
	// ������� ����������� �������� ���� � �������������� �������� ����
	const int m_defaultDelay = 250;
	int m_totalDelay = m_defaultDelay;

	// ������ ���
	Food m_food;
	// ������ ������
	Snake m_snake;
};

