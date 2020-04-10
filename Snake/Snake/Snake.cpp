#include "Snake.h"

Snake::Snake() { }

bool Snake::isHead(const std::pair<int, int> &head) const 
{
	return m_body.front().getPoint() == head;
}
bool Snake::isBody(const std::pair<int, int>& point) const
{
	// Looking for any of the matches with the coordinates of the body of the snake
	return std::any_of(m_body.cbegin(), m_body.cend(), [=](const Point &bodyPoint) {
		if (bodyPoint.getPoint() != m_body.front().getPoint() && bodyPoint.getPoint() == point) {
			return true;
		}

		return false;
	});
}

bool Snake::isUroboros(const std::pair<int, int>& head) const
{
	int iterator = 0;
	for (auto &point : m_body) {
		// A body shorter than 4 points is not relevant
		// Check for tail eating
		if (iterator > 3 && point.getPoint() == head) {
			return true;
		}
		++iterator;
	}

	return false;
}

void Snake::addNewBodyPoint(const std::pair<int, int>& newHead)
{
	// Add a new point to the body like a head
	Point point;
	point.setPoint(newHead);
	m_body.push_front(point);
}
void Snake::moveSnake(const std::pair<int, int> &newHead)
{
	std::pair<int, int> newPoint = newHead;

	// Updating the coordinates of body points
	for (auto &bodyPoint : m_body) {
		auto tempPoint = bodyPoint.getPoint();
		bodyPoint.setPoint(newPoint);
		newPoint = tempPoint;
	}
}
void Snake::restart()
{
	m_body.clear();
}
std::pair<int, int> Snake::getHead()
{
	return m_body.front().getPoint();
}
