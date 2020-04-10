#pragma once
#include <utility>

// Класс для наследования точки поде еду и тело змейки
class Point
{
public:
	Point();
	virtual ~Point();
	// Функции для установки и получения координат точки
	void setPoint(const std::pair<int, int> &point);
	std::pair<int, int> getPoint() const;
	int getPointX() const;
	int getPointY() const;

private:
	std::pair<int, int> m_point;
};
