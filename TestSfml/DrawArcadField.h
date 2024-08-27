#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "gameState.h"
#include "DrawField.h"

#include "Sounds.h"

extern int cellSize = 35;
extern int rows = 20;
extern int cols = 25;

enum direction { right, left, up, down };
direction dir;

void food(std::vector<std::vector<char>>& field) {
	int rows = field.size();
	int cols = field[0].size();
	srand(time(NULL));

	std::vector<std::pair<int, int>> freePositions;

	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			if (field[i][j] != 'O' && field[i][j] != '1') {
				freePositions.push_back({ i, j });
			}
		}
	}

	if (!freePositions.empty()) {
		int index = rand() % freePositions.size();
		field[freePositions[index].first][freePositions[index].second] = '@';
	}
}

bool foodCheck(std::vector<std::vector<char>>& field) {
	int rows = field.size();
	int cols = field[0].size();

	for (int i = 1; i < rows - 1; ++i) {
		for (int j = 1; j < cols - 1; ++j) {
			if (field[i][j] == '@')
				return true;
		}
	}
	return false;
}

void defaultArcad(sf::RenderWindow& window, int& headX, int& headY, int& snakeLength, gameState& state, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {
	switch (dir) {
	case left: headY -= 1; break;
	case right: headY += 1; break;
	case up: headX -= 1; break;
	case down: headX += 1; break;
	}

	if (headX < 0 || headX >= rows || headY < 0 || headY >= cols || field[headX][headY] == '1' || field[headX][headY] == 'O') {
		music.stop();
		endSound();
		state = END;
		return;
	}

	if (field[headX][headY] == '@') {
		snakeLength++;
		foodSound();
		food(field);
		++foodIndex;
	}

	if (foodCheck(field) == false) {
		food(field);
	}

	snake.insert(snake.begin(), { headX, headY });
	field[headX][headY] = 'O';

	if (snake.size() > snakeLength) {
		std::pair<int, int> tail = snake.back();
		snake.pop_back();
		field[tail.first][tail.second] = ' ';
	}
}

void firstArcad(sf::RenderWindow& window, int& headX, int& headY, int& snakeLength, gameState& state, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {
	switch (dir) {
	case left: headY -= 1; break;
	case right: headY += 1; break;
	case up: headX -= 1; break;
	case down: headX += 1; break;
	}

	if (headX < 0 || headX >= rows || headY < 0 || headY >= cols || field[headX][headY] == '1' || field[headX][headY] == 'O') {
		music.stop();
		endSound();
		state = END;
		return;
	}

	if (field[headX][headY] == '@') {
		snakeLength++;
		foodSound();
		food(field);
		++foodIndex;
	}

	if (foodCheck(field) == false) {
		food(field);
	}

	snake.insert(snake.begin(), { headX, headY });
	field[headX][headY] = 'O';

	if (snake.size() > snakeLength) {
		std::pair<int, int> tail = snake.back();
		snake.pop_back();
		field[tail.first][tail.second] = ' ';
	}
}

void chooceArcad(char& inputArcad, sf::RenderWindow& window, int& headX, int& headY, int& snakeLength, gameState& state, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {
	switch (inputArcad){
	case '1':
		firstArcad(window, headX, headY, snakeLength, state, field, snake);
		break;
	default:
		defaultArcad(window, headX, headY, snakeLength, state, field, snake);
	}
}
