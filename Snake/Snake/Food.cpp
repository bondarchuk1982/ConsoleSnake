#include "Food.h"

Food::Food() { }

// Функция задающая максимальные границы поля
void Food::setMaximumPoint(const std::pair<int, int>& maxPoint)
{
	m_maximumPoint = maxPoint;
}
// Функция генерации координат положения объекта на игровой доске
void Food::foodNextRandomPoint()
{
	std::pair<int, int> newPoint(0, 0);

	std::srand(unsigned(std::time(0)));

	// Генерируем до тех пор пока объект не будет в нутри поля и на новом месте
	while (newPoint.first == 0 || newPoint.first == m_maximumPoint.first ||
		   newPoint.second == 0 || newPoint.second == m_maximumPoint.second ||
		   newPoint == m_point)
	{
		newPoint.first = std::rand() % m_maximumPoint.first;
		newPoint.second = std::rand() % m_maximumPoint.second;
	}

	m_point = newPoint;
}

// Функция возврата координаты "x" положения объекта
int Food::getFoodX() const
{
	return m_point.first;
}
// Функция возврата координаты "y" положения объекта
int Food::getFoodY() const
{
	return m_point.second;
}
// Функция возврата точки расположения объекта
std::pair<int, int> Food::getFoodPoint() const
{
	return m_point;
}
