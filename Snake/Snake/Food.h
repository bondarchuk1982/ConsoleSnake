#pragma once
#include <utility>
#include <ctime>

#include "Point.h"
#include "Snake.h"

class Food : public Point
{
public:
	Food();
	// ������� ��� ���������� ����������� ���������
	void setMaximumBoundaries(const std::pair<int, int> &maxSize);
	void nextRandomPoint(const Snake &snake);

private:
	// �������
	std::pair<int, int> m_boundaries;
};

