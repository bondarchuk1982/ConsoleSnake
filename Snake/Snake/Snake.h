#pragma once
#include <utility>
#include <forward_list>
#include <algorithm>

class Snake
{
public:
	Snake();

	// Функции для проверки совпадений
	bool isHead(const std::pair<int, int> &head) const;
	bool isBody(const std::pair<int, int> &point) const;
	bool isUroboros(const std::pair<int, int> &head) const;

	// Функции для управления внутренними объектами
	void addNewBodyPoint(const std::pair<int, int> &newHead);
	void moveSnake(const std::pair<int, int> &newHead);
	void restart();

	// Функция для получения внутреннего объекта
	std::pair<int, int> getHead();

private:
	// Мембер
	std::forward_list<std::pair<int, int>> m_body;
};

