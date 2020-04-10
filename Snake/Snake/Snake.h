#pragma once
#include <utility>
#include <forward_list>
#include <algorithm>

#include "Point.h"

class Snake
{
public:
	Snake();

	// Функции для проверки совпадений
	bool isHead(const std::pair<int, int> &head) const;
	bool isBody(const std::pair<int, int> &point) const;
	bool isUroboros(const std::pair<int, int> &head) const;

	// Функции для управления внутренними объектами
	void addNewBodyPoint(const std::pair<int, int> &newHead); // Уведичиваем размер змейки
	void moveSnake(const std::pair<int, int> &newHead); // Двигаем тело змейки
	void restart(); // Удаляем тело змейки

	// Функция для получения координат головы змейки
	std::pair<int, int> getHead();

private:
	// Мембер
	std::forward_list<Point> m_body;
};

