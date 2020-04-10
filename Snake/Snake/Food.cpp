#include "Food.h"

Food::Food() { }

void Food::setMaximumBoundaries(const std::pair<int, int>& boundaries)
{
	m_boundaries = boundaries;
}
void Food::nextRandomPoint(const Snake &snake)
{
	std::pair<int, int> newPoint(0, 0);

	std::srand(unsigned(std::time(0)));

	// Check if the coordinates are on the border or on old point, or on the body of the snake
	while (newPoint.first == 0 || newPoint.first == m_boundaries.first ||
		   newPoint.second == 0 || newPoint.second == m_boundaries.second ||
		   newPoint == getPoint() || snake.isBody(newPoint))
	{
		newPoint.first = std::rand() % m_boundaries.first;
		newPoint.second = std::rand() % m_boundaries.second;
	}

	setPoint(newPoint);
}
