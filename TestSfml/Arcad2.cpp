#include "Arcad2.h"
#include "Sounds.h"
#include <iostream>

std::vector<std::vector<char>> secondField() {
	const char* customField[] = {
		"1111111111111111111111111",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
		"1000000000000000000000001",
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

void unFood(std::vector<std::vector<char>>& secondField) {
	int rows = secondField.size();
	int cols = secondField[0].size();

	std::vector<std::pair<int, int>> freePositions;

	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			if (secondField[i][j] != 'O' && secondField[i][j] != '1') {
				freePositions.push_back({ i, j });
			}
		}
	}

	if (!freePositions.empty()) {
		for (int i = 1; i < rows - 1; ++i) {
			for (int j = 1; j < cols - 1; ++j) {
				if (secondField[i][j] == '2') {
					secondField[i][j] = ' ';
				}
			}
		}

		for (int i = 0; i < 7; ++i) {
			int index = rand() % freePositions.size();
			secondField[freePositions[index].first][freePositions[index].second] = '2';
		}
	}
}

void secondArcadLogic(sf::RenderWindow& window, int& headX, int& headY, int& snakeLength, gameState& state, std::vector<std::vector<char>>& secondField, std::vector<std::pair<int, int>>& snake, bool checkSound) {
	switch (dir) {
	case left: headY -= 1; break;
	case right: headY += 1; break;
	case up: headX -= 1; break;
	case down: headX += 1; break;
	}

	if (headX < 0 || headX >= rows || headY < 0 || headY >= cols || secondField[headX][headY] == '1' || secondField[headX][headY] == 'O') {
		music.stop();
		endSound(checkSound);
		state = END;
		return;
	}

	if (secondField[headX][headY] == '@') {
		snakeLength++;
		foodSound(checkSound);
		food(secondField);
		++foodIndex;
	}

	if (foodCheck(secondField) == false) {
		food(secondField);
	}

	if (secondField[headX][headY] == '2') {
		snakeLength--;
		foodSound(checkSound);

		if (snakeLength < 1) {
			music.stop();
			endSound(checkSound);
			state = END;
			return;
		}

		if (snake.size() > snakeLength) {
			std::pair<int, int> tail = snake.back();
			snake.pop_back();
			secondField[tail.first][tail.second] = ' ';
		}
	}

	snake.insert(snake.begin(), { headX, headY });
	secondField[headX][headY] = 'O';

	if (snake.size() > snakeLength) {
		std::pair<int, int> tail = snake.back();
		snake.pop_back();
		secondField[tail.first][tail.second] = ' ';
	}
}
