#include "Snake.h"

Snake::Snake() { }

// ������� �������� �������� �� ���������� ���������� ������� ������
bool Snake::isHead(const std::pair<int, int> &head) const 
{
	return m_body.front().getPoint() == head;
}
// ������� �������� �������� �� ���������� ���������� ������ ���� ������
bool Snake::isBody(const std::pair<int, int>& point) const
{
	return std::any_of(m_body.cbegin(), m_body.cend(), [=](const Point &bodyPoint) {
		if (bodyPoint.getPoint() != m_body.front().getPoint() && bodyPoint.getPoint() == point) {
			return true;
		}

		return false;
	});
}
// ������� �������� ������ �� ������ ������ ���� �����
bool Snake::isUroboros(const std::pair<int, int>& head) const
{
	int iterator = 0;
	for (auto &point : m_body) {
		// �������� ��������� ��� ������� ���� ������ 4 �����
		if (iterator > 3 && point.getPoint() == head) {
			return true;
		}
		++iterator;
	}

	return false;
}
// ������� ����������� ���� ������
void Snake::addNewBodyPoint(const std::pair<int, int>& newHead)
{
	Point point;
	point.setPoint(newHead);
	m_body.push_front(point);
}
// ������� ���������� ���� ������
void Snake::moveSnake(const std::pair<int, int> &newHead)
{
	std::pair<int, int> newPoint = newHead;

	// ���������� ���� ������, ��� ����� ������������ ���������� ����� ����
	for (auto &bodyPoint : m_body) {
		auto point = bodyPoint.getPoint();
		bodyPoint.setPoint(newPoint);
		newPoint = point;
	}
}
// ������� ������� ���� ������ ��� �������� ����
void Snake::restart()
{
	m_body.clear();
}
// ������� ���������� ���������� ������ ������
std::pair<int, int> Snake::getHead()
{
	return m_body.front().getPoint();
}
