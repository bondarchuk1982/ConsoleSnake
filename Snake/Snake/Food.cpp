#include "Food.h"

Food::Food() { }

// ������� �������� ������������ ������� ����
void Food::setMaximumPoint(const std::pair<int, int>& maxPoint)
{
	m_maximumPoint = maxPoint;
}
// ������� ��������� ��������� ��������� ������� �� ������� �����
void Food::foodNextRandomPoint()
{
	std::pair<int, int> newPoint(0, 0);

	std::srand(unsigned(std::time(0)));

	// ���������� �� ��� ��� ���� ������ �� ����� � ����� ���� � �� ����� �����
	while (newPoint.first == 0 || newPoint.first == m_maximumPoint.first ||
		   newPoint.second == 0 || newPoint.second == m_maximumPoint.second ||
		   newPoint == m_point)
	{
		newPoint.first = std::rand() % m_maximumPoint.first;
		newPoint.second = std::rand() % m_maximumPoint.second;
	}

	m_point = newPoint;
}

// ������� �������� ���������� "x" ��������� �������
int Food::getFoodX() const
{
	return m_point.first;
}
// ������� �������� ���������� "y" ��������� �������
int Food::getFoodY() const
{
	return m_point.second;
}
// ������� �������� ����� ������������ �������
std::pair<int, int> Food::getFoodPoint() const
{
	return m_point;
}
