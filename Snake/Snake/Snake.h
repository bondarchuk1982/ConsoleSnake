#pragma once
#include <utility>
#include <forward_list>
#include <algorithm>

#include "Point.h"

class Snake
{
public:
	Snake();

	bool isHead(const std::pair<int, int> &head) const; // Head check
	bool isBody(const std::pair<int, int> &point) const; // Body check
	bool isUroboros(const std::pair<int, int> &head) const; // Tail check

	void addNewBodyPoint(const std::pair<int, int> &newHead); // Body size increase
	void moveSnake(const std::pair<int, int> &newHead); // Move the body
	void restart(); // Clean the body

	std::pair<int, int> getHead(); // Get head coordinates

private:
	std::forward_list<Point> m_body; // Private member snake body
};

