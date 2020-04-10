#pragma once

using namespace std;
// Status game
enum GameStatus {
	GameMenu,
	GameStart,
	GameOver,
	GameDemo,
	Exit
} gameStatus;
// Movement mode
enum Movement {
	Stop,
	Left,
	Right,
	Up,
	Down
} movement;