#include "Board.h"
#include "Enums.h"

Board::Board()
{
	m_food.setMaximumPoint(std::pair<int, int>(m_width, m_height));
}

// ��� ������ ������ ��������� ��� �������
void Board::run(std::atomic_int &keyPressed)
{
	gameStatus = GameStatus::GameMenu;
	menu();

	restartGame();
	movement = Movement::Stop;

	// ����������� ������ ����
	while (gameStatus != GameStatus::Exit)
	{
		keyPressedToGameStatus(keyPressed);

		if (gameStatus == GameStatus::GameStart) {
			keyPressedToMovement(keyPressed);
			logic();
			drawBoard();
		}
		else if (gameStatus == GameStatus::GameDemo) {
			demo();
			drawBoard();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(m_delay));
	}
}
// ������� �������� ������ ����
void Board::logic()
{
	moveSnake();
	checkFood();
	checkGameOver();
}
// ������� ���� ������ ����
void Board::demo()
{
	autoMove();
	logic();
}
// ������� ��������� ������� �����
void Board::drawBoard()
{
	system("cls");
	for (int y = 0; y <= m_height; ++y) {
		for (int x = 0; x <= m_width; ++x) {
			if (x == 0 && x != m_width) cout << "#";
			else if (y == 0 && x == m_width) cout << "#  SCORE: " << m_score;
			else if (x == m_width) cout << "#";
			else if (y == 0 || y == m_height) cout << "#";
			else if (x == m_food.getFoodX() && y == m_food.getFoodY()) cout << "F";
			else if (m_snake.isHead(std::pair<int, int>(x, y))) cout << "O";
			else if (m_snake.isBody(std::pair<int, int>(x, y))) cout << "o";
			else cout << " ";
		}
		cout << endl;
	}

	drawGameStatus();
}
// ������� ������� ������� ����
void Board::drawGameStatus()
{
	cout << endl;
	cout << "Game status: ";

	switch (gameStatus)
	{
	case GameStart: cout << "GAME START!" << endl; break;
	case GameOver:  cout << "GAME OVER!" << endl;  break;
	case GameDemo:  cout << "DEMO" << endl;	       break;
	}
}
// ������� ������ ���������� ����
void Board::menu()
{
	cout << endl;
	cout << "MENU:" << endl;
	cout << "s - start game" << endl;
	cout << "d - demo game" << endl;
	cout << "x - exit" << endl;
	cout << endl;

	cout << "Control:" << endl;
	cout << "Up - arrowUp" << endl; 
	cout << "Down - arrowDown" << endl;
	cout << "Left - arrowLeft" << endl;
	cout << "Right - arrowRight" << endl;
}
// ������� ����������� ��������� ���������� ��� �������� ����
void Board::restartGame()
{
	m_food.foodNextRandomPoint();

	m_snake.restart();
	m_snake.addNewBodyPoint(std::pair<int, int>(m_width / 2, m_height / 2));

	m_delay = 200;
	m_score = 0;
}
// ������� �������� ������
void Board::moveSnake()
{
	auto newHead = m_snake.getHead();

	switch (movement)
	{
	case Left:  --newHead.first;  break;
	case Right: ++newHead.first;  break;
	case Up:    --newHead.second; break;
	case Down:  ++newHead.second; break;
	}

	if (newHead != m_snake.getHead()) {
		m_snake.moveSnake(newHead);
	}
}
// ������� ��������������� �������� ������ ��� ���� ������
void Board::autoMove()
{
	const auto &head = m_snake.getHead();
	const auto &food = m_food.getFoodPoint();
	
	if (food.first >= head.first && food.second <= head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Left ? movement = Movement::Up : movement = Movement::Right :
			movement == Movement::Down ? movement = Movement::Right : movement = Movement::Up;
	}
	else if (food.first > head.first && food.second >= head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Left ? movement = Movement::Down : movement = Movement::Right :
			movement == Movement::Up ? movement = Movement::Right : movement = Movement::Down;
	}
	else if (food.first <= head.first && food.second > head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Right ? movement = Movement::Down : movement = Movement::Left :
			movement == Movement::Up ? movement = Movement::Left : movement = Movement::Down;
	}
	else if (food.first < head.first && food.second < head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Right ? movement = Movement::Up : movement = Movement::Left :
			movement == Movement::Down ? movement = Movement::Left : movement = Movement::Up;
	}
}
// ������� �������� �������� ��� �������
void Board::checkFood()
{
	if (m_snake.isHead(m_food.getFoodPoint())) {
		++m_score;
		m_snake.addNewBodyPoint(m_food.getFoodPoint());
		m_food.foodNextRandomPoint();

		if (m_delay > 50) {
			m_delay -= 5;
		}
	}
}
// ������� �������� �� ���������� ����
void Board::checkGameOver()
{
	if (checkWalls() || m_snake.isUroboros(m_snake.getHead())) {
		movement = Movement::Stop;
		gameStatus = GameStatus::GameOver;
	}
}
// ������� ������������ ������� ���� � ����������� �� ������� ������������� �������
void Board::keyPressedToGameStatus(std::atomic_int &keyPressed)
{
	switch (keyPressed)
	{
		// "d" - ���� ����� ����
	case 100: if (gameStatus != GameStatus::GameStart) {
		restartGame();
		gameStatus = GameStatus::GameDemo;
		keyPressed = 0;
	} break;
		// "s" - ����� ����
	case 115: if (gameStatus != GameStatus::GameStart) {
		restartGame();
		gameStatus = GameStatus::GameStart;
		keyPressed = 72;
	} break;
		// "x"- ����� �� ����
	case 120: gameStatus = GameStatus::Exit; break;
	}
}
// ������� ���������� �������
void Board::keyPressedToMovement(const std::atomic_int &keyPressed)
{
	switch (keyPressed) {
		// "arrowUp" - ������� �����
	case 72:  if (movement != Movement::Down)  movement = Movement::Up;    break;
		// "arrowLeft" - ������� � ����
	case 75:  if (movement != Movement::Right) movement = Movement::Left;  break;
		// "arrowRight" - ������� � �����
	case 77:  if (movement != Movement::Left)  movement = Movement::Right; break;
		// "arrowDown" - ������� � ���
	case 80:  if (movement != Movement::Up)    movement = Movement::Down;  break;
	}
}
//������� �������� ����������� ������ �� �������
bool Board::checkWalls()
{
	const auto &head = m_snake.getHead();

	if (head.first == 0 || head.first == m_width || head.second == 0 || head.second == m_height) {
		return true;
	}

	return false;
}
