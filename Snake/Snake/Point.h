#pragma once
#include <utility>

class Point
{
public:
	Point();
	virtual ~Point(); // Virtual destructor for inheritance
	void setPoint(const std::pair<int, int> &point); // Set coordinats for point
	std::pair<int, int> getPoint() const; // Get point coordinats
	int getPointX() const; // Get point coordinat X
	int getPointY() const; // Get point coordinat Y

private:
	std::pair<int, int> m_point; // Private member
};
