#pragma once
#include <utility>
#include <ctime>

#include "Point.h"
#include "Snake.h"

class Food : public Point
{
public:
	Food();
	void setMaximumBoundaries(const std::pair<int, int> &maxSize); // Set maximum boundaries board
	void nextRandomPoint(const Snake &snake); // Generate random coordinates

private:
	std::pair<int, int> m_boundaries; // Private member for boundaries
};

