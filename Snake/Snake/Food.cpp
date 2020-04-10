#include "Food.h"

Food::Food() { }

// Функция задающая максимальные границы поля
void Food::setMaximumBoundaries(const std::pair<int, int>& boundaries)
{
	m_boundaries = boundaries;
}
// Функция генерации координат положения объекта на игровой доске
void Food::nextRandomPoint(const Snake &snake)
{
	std::pair<int, int> newPoint(0, 0);

	std::srand(unsigned(std::time(0)));

	// Генерируем до тех пор пока объект не будет в нутри поля и на новом месте
	while (newPoint.first == 0 || newPoint.first == m_boundaries.first ||
		   newPoint.second == 0 || newPoint.second == m_boundaries.second ||
		   newPoint == getPoint() || snake.isBody(newPoint))
	{
		newPoint.first = std::rand() % m_boundaries.first;
		newPoint.second = std::rand() % m_boundaries.second;
	}

	setPoint(newPoint);
}
