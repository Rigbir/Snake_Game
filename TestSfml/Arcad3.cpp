#include "Arcad1.h"
#include "Sounds.h"
#include "Arcad3.h"

std::vector<std::vector<char>> thirdField() {
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

void thirdArcadLogic(sf::RenderWindow& window, int& headX, int& headY, int& snakeLength, gameState& state, std::vector<std::vector<char>>& thirdField, std::vector<std::pair<int, int>>& snake) {
	switch (dir) {
	case left: headY -= 1; break;
	case right: headY += 1; break;
	case up: headX -= 1; break;
	case down: headX += 1; break;
	}

	int elapsedTime = levelTimer.getElapsedTime().asSeconds();
	if (elapsedTime >= timeLevel) {
		if (snakeLength < foodForNextLevel) {
			music.stop();
			endSound();
			state = END;
			return;
		}
		else{
			for (const auto& segment : snake) {
				thirdField[segment.first][segment.second] = ' ';
			}

			snake.clear();
			snake.push_back({ headX, headY });
			snakeLength = 1;
			levelTimer.restart();

			if (sp == third) {
				timeLevel = 20;
				sp = add;
			}
			else if (sp == add) {
				timeLevel = 15;
				sp = second;
			}
			else if (sp == second) {
				timeLevel = 13;
				sp = first;
			}
			else if (sp == first) {
				music.stop();
				win = true;
				state = END;
				return;
			}
		}
	}

	if (headX < 0 || headX >= rows || headY < 0 || headY >= cols || thirdField[headX][headY] == '1' || thirdField[headX][headY] == 'O') {
		music.stop();
		endSound();
		state = END;
		return;
	}

	if (thirdField[headX][headY] == '@') {
		snakeLength++;
		foodSound();
		food(thirdField);
		++foodIndex;
	}

	if (foodCheck(thirdField) == false) {
		food(thirdField);
	}

	snake.insert(snake.begin(), { headX, headY });
	thirdField[headX][headY] = 'O';

	if (snake.size() > snakeLength) {
		std::pair<int, int> tail = snake.back();
		snake.pop_back();
		thirdField[tail.first][tail.second] = ' ';
	}
}