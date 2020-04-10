#include "Point.h"

Point::Point() { }
Point::~Point() { }

void Point::setPoint(const std::pair<int, int>& point)
{
	if (m_point == point) {
		return;
	}

	m_point = point;
}
std::pair<int, int> Point::getPoint() const
{
	return m_point;
}
int Point::getPointX() const
{
	return m_point.first;
}
int Point::getPointY() const
{
	return m_point.second;
}
