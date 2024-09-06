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

void thirdArcadLogic(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& thirdField, std::vector<std::pair<int, int>>& snake) {
	switch (dir) {
	case left: headY -= 1; break;
	case right: headY += 1; break;
	case up: headX -= 1; break;
	case down: headX += 1; break;
	}

	float elapsedTime = levelTimer.getElapsedTime().asSeconds();
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

void timeArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField) {
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	size_t rows = thirdField.size();
	size_t cols = thirdField[0].size();

	textTime.setFont(font);
	textTime.setCharacterSize(36);
	textTime.setFillColor(sf::Color(255, 250, 205));
	textTime.setStyle(sf::Text::Bold);

	float elapsedTime = timeLevel - levelTimer.getElapsedTime().asSeconds();
	if (elapsedTime < 0) elapsedTime = 0;

	textTime.setString("Time: " + std::to_string(elapsedTime));

	sf::FloatRect textRect = textTime.getGlobalBounds();

	textTime.setPosition(static_cast<float>(offsetX + (cols * cellSize - textRect.width) / 2),
		static_cast<float>(offsetY + (rows * cellSize - textRect.height - 924) / 2));

	window.draw(textTime);
}

void scoreArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField) {
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	size_t rows = thirdField.size();
	size_t cols = thirdField[0].size();

	sf::Text text;
	text.setFont(font);

	int scoreElapsed = foodForNextLevel - snakeLength;
	if (scoreElapsed < 0) scoreElapsed = 0;
	text.setString("Score: " + std::to_string(scoreElapsed));

	text.setCharacterSize(36);
	text.setFillColor(sf::Color(255, 250, 205));
	text.setStyle(sf::Text::Bold);

	sf::FloatRect textRect = text.getGlobalBounds();

	text.setPosition(static_cast<float>(offsetX + (cols * cellSize - textRect.width) / 2),
		static_cast<float>(offsetY + rows * cellSize - textRect.height - 134));

	window.draw(text);
}
