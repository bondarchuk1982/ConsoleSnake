#include "Snake.h"

Snake::Snake() { }

// Функция проверки являются ли переданные координаты головой змейки
bool Snake::isHead(const std::pair<int, int> &head) const 
{
	return m_body.front() == head;
}
// Функция проверки являются ли переданные координаты точкой тела змейки
bool Snake::isBody(const std::pair<int, int>& point) const
{
	return std::any_of(m_body.cbegin(), m_body.cend(), [=](const std::pair<int, int>& bodyPoint) {
		if (bodyPoint != m_body.front() && bodyPoint == point) {
			return true;
		}

		return false;
	});
}
// Функция проверки уксила ли голова змейки свой хвост
bool Snake::isUroboros(const std::pair<int, int>& head) const
{
	int iterator = 0;
	for (auto &point : m_body) {
		// Проверка актуальна при размере тела больше 4 точек
		if (iterator > 3 && point == head) {
			return true;
		}
		++iterator;
	}

	return false;
}
// Функция увеличивает тело змейки
void Snake::addNewBodyPoint(const std::pair<int, int>& newHead)
{
	m_body.push_front(newHead);
}
// Функция перемещает тело змейки
void Snake::moveSnake(const std::pair<int, int> &newHead)
{
	std::pair<int, int> pointBody = newHead;

	// Перемещаем тело змейки, для этого переписываем координаты точек тела
	for (auto &body : m_body) {
		auto point = body;
		body = pointBody;
		pointBody = point;
	}
}
// Функция очистки тела змейки для рестарта игры
void Snake::restart()
{
	m_body.clear();
}
// Функция возвращает координаты головы змейки
std::pair<int, int> Snake::getHead()
{
	return m_body.front();
}
