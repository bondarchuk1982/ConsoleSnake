#pragma once

using namespace std;
// ������������ ������� ����
enum GameStatus {
	GameMenu,
	GameStart,
	GameOver,
	GameDemo,
	Exit
} gameStatus;
// ������������ ��������� ������
enum Movement {
	Stop,
	Left,
	Right,
	Up,
	Down
} movement;