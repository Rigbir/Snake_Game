#include "Arcad4.h"
#include "Arcad1.h"
#include "Arcad3.h"

bool flagStyle = false;
int count = 1;
int next = 2;

void fourthArcadLogic(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& thirdField, std::vector<std::pair<int, int>>& snake) {
	switch (dir) {
	case left: headY -= 1; break;
	case right: headY += 1; break;
	case up: headX -= 1; break;
	case down: headX += 1; break;
	}

	if (snakeLength == foodForNextLevel * count) flagStyle = false;

	if ((snakeLength == foodForNextLevel * count) && !flagStyle) {
		inputStyle = static_cast<char>('0' + next);
		std::cout << "Input Style: " << inputStyle << '\n';
		++next;
		++count;
		flagStyle = true;
		foodIndex = 0;
	}
	
	if (snakeLength == foodForNextLevel * 8) {
		music.stop();
		win = true;
		state = END;
		return;
	}

	if (headX < 0 || headX >= rows || headY < 0 || headY >= cols || thirdField[headX][headY] == '1' || thirdField[headX][headY] == 'O') {
		music.stop();
		endSound();
		sf::sleep(sf::milliseconds(100));
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
