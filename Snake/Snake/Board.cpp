#include "Board.h"
#include "Enums.h"

Board::Board()
{
	m_food.setMaximumBoundaries(std::pair<int, int>(m_width, m_height));
}

void Board::run(std::atomic_int &keyPressed)
{
	// Start game menu
	gameStatus = GameStatus::GameMenu;
	menu();

	restartGame();
	movement = Movement::Stop;

	// Game Status Check Cycle
	while (gameStatus != GameStatus::Exit)
	{
		// Checking the switching of the game status by the user
		keyPressedToGameStatus(keyPressed);

		if (gameStatus == GameStatus::GameStart) {
			keyPressedToMovement(keyPressed); // Check the control of the snake
			logic();
			drawBoard();
		}
		else if (gameStatus == GameStatus::GameDemo) {
			demo();
			drawBoard();
		}

		// To control the speed of the game
		std::this_thread::sleep_for(std::chrono::milliseconds(m_totalDelay));
	}
}
void Board::logic()
{
	moveSnake();
	checkFood();
	checkGameOver();
}
void Board::demo()
{
	autoMove();
	logic();
}
void Board::drawBoard()
{
	system("cls");
	for (int y = 0; y <= m_height; ++y) {
		for (int x = 0; x <= m_width; ++x) {
			if (x == 0 && x != m_width) cout << "#"; // The first line of the board
			else if (y == 0 && x == m_width) cout << "#  SCORE: " << m_score; // Score at the end of the first line
			else if (x == m_width) cout << "#"; // The last colum of the board
			else if (y == 0 || y == m_height) cout << "#"; // The first colum and last line of the board
			else if (x == m_food.getPointX() && y == m_food.getPointY()) cout << "F"; // Food on the board
			else if (m_snake.isHead(std::pair<int, int>(x, y))) cout << "O"; // Head snake on the board
			else if (m_snake.isBody(std::pair<int, int>(x, y))) cout << "o"; // Body snake on the board
			else cout << " "; // Empty point on the board
		}
		cout << endl;
	}

	drawGameStatus(); // Game status at the end
}
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
void Board::restartGame()
{
	m_snake.restart(); // Clear body
	m_snake.addNewBodyPoint(std::pair<int, int>(m_width / 2, m_height / 2)); // Reset head snake
	m_food.nextRandomPoint(m_snake); // Reset food point

	m_totalDelay = m_defaultDelay; // Reset game speed
	m_score = 0; // Reset game score
}
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
void Board::autoMove()
{
	const auto &head = m_snake.getHead();
	const auto &food = m_food.getPoint();
	
	// If the food is on the right from the top
	if (food.first >= head.first && food.second <= head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Left ? movement = Movement::Up : movement = Movement::Right :
			movement == Movement::Down ? movement = Movement::Right : movement = Movement::Up;
	}
	// If the food is from the bottom right
	else if (food.first > head.first && food.second >= head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Left ? movement = Movement::Down : movement = Movement::Right :
			movement == Movement::Up ? movement = Movement::Right : movement = Movement::Down;
	}
	// If the food is from the left to the bottom
	else if (food.first <= head.first && food.second > head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Right ? movement = Movement::Down : movement = Movement::Left :
			movement == Movement::Up ? movement = Movement::Left : movement = Movement::Down;
	}
	// If the food is from the top left
	else if (food.first < head.first && food.second < head.second) {
		std::abs(head.first - food.first) >= std::abs(head.second - food.second) ?
			movement == Movement::Right ? movement = Movement::Up : movement = Movement::Left :
			movement == Movement::Down ? movement = Movement::Left : movement = Movement::Up;
	}
}
void Board::checkFood()
{
	// If the head eats food
	if (m_snake.isHead(m_food.getPoint())) {
		++m_score;
		m_snake.addNewBodyPoint(m_food.getPoint()); // Increase the body
		m_food.nextRandomPoint(m_snake); // Next random food point

		if (m_totalDelay > 25) {
			m_totalDelay -= 5; // Game speed up
		}
	}
}
void Board::checkGameOver()
{
	// Game over if the head is on the wall or on the tail
	if (checkWalls() || m_snake.isUroboros(m_snake.getHead())) {
		movement = Movement::Stop;
		gameStatus = GameStatus::GameOver;
	}
}
void Board::keyPressedToGameStatus(std::atomic_int &keyPressed)
{
	switch (keyPressed)
	{
		// button "d" - demo mode
	case 100: if (gameStatus != GameStatus::GameStart) {
		restartGame();
		gameStatus = GameStatus::GameDemo;
		keyPressed = 0;
	} break;
		// button "s" - start game
	case 115: if (gameStatus != GameStatus::GameStart) {
		restartGame();
		gameStatus = GameStatus::GameStart;
		keyPressed = 72;
	} break;
		// button "x"- exit game
	case 120: gameStatus = GameStatus::Exit; break;
	}
}
void Board::keyPressedToMovement(const std::atomic_int &keyPressed)
{
	switch (keyPressed) {
		// button "arrowUp" - move up
	case 72:  if (movement != Movement::Down)  movement = Movement::Up;    break;
		// button "arrowLeft" - move left
	case 75:  if (movement != Movement::Right) movement = Movement::Left;  break;
		// button "arrowRight" - move right
	case 77:  if (movement != Movement::Left)  movement = Movement::Right; break;
		// button "arrowDown" - move down
	case 80:  if (movement != Movement::Up)    movement = Movement::Down;  break;
	}
}
bool Board::checkWalls()
{
	const auto &head = m_snake.getHead();

	// If the head is on the wall
	if (head.first == 0 || head.first == m_width || head.second == 0 || head.second == m_height) {
		return true;
	}

	return false;
}
