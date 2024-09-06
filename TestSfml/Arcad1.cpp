#include "Arcad1.h"
#include "Arcad2.h"
#include "Arcad3.h"
#include "Sounds.h"

sf::Clock unFoodTimer;
sf::Time unFoodElapsed;

std::vector<std::vector<char>> firstField() {
	const char* customField[] = {
		"1111111111111111111111111",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000111000001110000001",
		"1000000100000000010000001",
		"1000000100000000010000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000100000000010000001",
		"1000000100000000010000001",
		"1000000111000001110000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1111111111111111111111111"
	};

	std::vector<std::vector<char>> field(rows, std::vector<char>(cols));

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			field[i][j] = customField[i][j];
		}
	}

	return field;
}

void food(std::vector<std::vector<char>>& firstField) {
	size_t rows = firstField.size();
	size_t cols = firstField[0].size();

	std::vector<std::pair<int, int>> freePositions;

	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			if (firstField[i][j] != 'O' && firstField[i][j] != '1' && firstField[i][j] != '2') {
				freePositions.push_back({ i, j });
			}
		}
	}

	if (!freePositions.empty()) {
		int index = rand() % freePositions.size();
		firstField[freePositions[index].first][freePositions[index].second] = '@';
	}
}

bool foodCheck(std::vector<std::vector<char>>& firstField) {
	size_t rows = firstField.size();
	size_t cols = firstField[0].size();

	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			if (firstField[i][j] == '@')
				return true;
		}
	}
	return false;
}

void firstArcadLogic(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& firstField, std::vector<std::pair<int, int>>& snake) {
	switch (dir) {
	case left: headY -= 1; break;
	case right: headY += 1; break;
	case up: headX -= 1; break;
	case down: headX += 1; break;
	}

	if (headX < 0 || headX >= rows || headY < 0 || headY >= cols || firstField[headX][headY] == '1' || firstField[headX][headY] == 'O') {
		music.stop();
		endSound();
		state = END;
		return;
	}

	if (firstField[headX][headY] == '@') {
		snakeLength++;
		foodSound();
		food(firstField);
		++foodIndex;
	}

	if (foodCheck(firstField) == false) {
		food(firstField);
	}

	snake.insert(snake.begin(), { headX, headY });
	firstField[headX][headY] = 'O';

	if (snake.size() > snakeLength) {
		std::pair<int, int> tail = snake.back();
		snake.pop_back();
		firstField[tail.first][tail.second] = ' ';
	}
}

void chooceArcad(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& firstField, std::vector<std::pair<int, int>>& snake) {
	switch (inputArcad) {
	case '1':
		firstArcadLogic(window, state, firstField, snake);
		break;
	case '2':
		secondArcadLogic(window, state, firstField, snake);
		unFoodElapsed = unFoodTimer.getElapsedTime();
		if (unFoodElapsed.asSeconds() >= 3.2f) {
			unFood(firstField);
			unFoodTimer.restart();
		}
		break;
	case '3':
		thirdArcadLogic(window, state, firstField, snake);
		break;
	default:
		firstArcadLogic(window, state, firstField, snake);
		break;
	}
}