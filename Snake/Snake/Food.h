#pragma once
#include <utility>
#include <ctime>

#include "Point.h"
#include "Snake.h"

class Food : public Point
{
public:
	Food();
	// Функции для управления внутренними объектами
	void setMaximumBoundaries(const std::pair<int, int> &maxSize);
	void nextRandomPoint(const Snake &snake);

private:
	// Мемберы
	std::pair<int, int> m_boundaries;
};

