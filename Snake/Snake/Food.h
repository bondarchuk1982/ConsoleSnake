#pragma once
#include <utility>
#include <ctime>

class Food
{
public:
	Food();
	// Функции для управления внутренними объектами
	void setMaximumPoint(const std::pair<int, int> &maxPoint);
	void foodNextRandomPoint();

	// Функции для доступа к внутренним объекта
	int getFoodX() const;
	int getFoodY() const;

	std::pair<int, int> getFoodPoint() const;

private:
	// Мемберы
	std::pair<int, int> m_point;
	std::pair<int, int> m_maximumPoint;
};

