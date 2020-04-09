#pragma once
#include <utility>
#include <ctime>

class Food
{
public:
	Food();
	// ������� ��� ���������� ����������� ���������
	void setMaximumPoint(const std::pair<int, int> &maxPoint);
	void foodNextRandomPoint();

	// ������� ��� ������� � ���������� �������
	int getFoodX() const;
	int getFoodY() const;

	std::pair<int, int> getFoodPoint() const;

private:
	// �������
	std::pair<int, int> m_point;
	std::pair<int, int> m_maximumPoint;
};

