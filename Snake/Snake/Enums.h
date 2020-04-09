#pragma once

using namespace std;
// Перечисление статуса игры
enum GameStatus {
	GameMenu,
	GameStart,
	GameOver,
	GameDemo,
	Exit
} gameStatus;
// Перечисления длвижения змейки
enum Movement {
	Stop,
	Left,
	Right,
	Up,
	Down
} movement;