#include "Snake.h"

Snake::Snake() { }

// ������� �������� �������� �� ���������� ���������� ������� ������
bool Snake::isHead(const std::pair<int, int> &head) const 
{
	return m_body.front() == head;
}
// ������� �������� �������� �� ���������� ���������� ������ ���� ������
bool Snake::isBody(const std::pair<int, int>& point) const
{
	return std::any_of(m_body.cbegin(), m_body.cend(), [=](const std::pair<int, int>& bodyPoint) {
		if (bodyPoint != m_body.front() && bodyPoint == point) {
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
		if (iterator > 3 && point == head) {
			return true;
		}
		++iterator;
	}

	return false;
}
// ������� ����������� ���� ������
void Snake::addNewBodyPoint(const std::pair<int, int>& newHead)
{
	m_body.push_front(newHead);
}
// ������� ���������� ���� ������
void Snake::moveSnake(const std::pair<int, int> &newHead)
{
	std::pair<int, int> pointBody = newHead;

	// ���������� ���� ������, ��� ����� ������������ ���������� ����� ����
	for (auto &body : m_body) {
		auto point = body;
		body = pointBody;
		pointBody = point;
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
	return m_body.front();
}
