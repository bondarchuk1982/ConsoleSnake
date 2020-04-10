#pragma once
#include <utility>

// ����� ��� ������������ ����� ���� ��� � ���� ������
class Point
{
public:
	Point();
	virtual ~Point();
	// ������� ��� ��������� � ��������� ��������� �����
	void setPoint(const std::pair<int, int> &point);
	std::pair<int, int> getPoint() const;
	int getPointX() const;
	int getPointY() const;

private:
	std::pair<int, int> m_point;
};
