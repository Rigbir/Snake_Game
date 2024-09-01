#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <windows.h>

#include "globals.h"
#include "resource.h"
#include "Button.h"
#include "Style.h"
#include "gameState.h"
#include "Style_manger.h"
#include "Arcad_manger.h"
#include "CursorTexture.h"
#include "DrawField.h"

#include "Sounds.h"

#include "Arcad1.h"
#include "Arcad2.h"
#include "Arcad3.h"

#define RED_TEXT "\033[1;31m"
#define WHITE_TEXT "\033[1;37m"
#define PURPLE_TEXT "\033[1;35m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[0;94m"

#define RESET_TEXT "\033[0m"

void endGame(int& snakeLength, gameState& state);

std::vector<std::vector<char>> barier() {
	std::vector<std::vector<char>> box(rows);

	box[0] = std::vector<char>(cols, '1');
	box[rows - 1] = std::vector<char>(cols, '1');

	for (int i = 1; i < rows - 1; ++i) {
		box[i] = std::vector<char>(cols, ' ');
		box[i][0] = '1';
		box[i][cols - 1] = '1';
	}

	return box;
}

void startPosition(std::vector<std::vector<char>>& field, int& headX, int& headY, std::vector<std::pair<int, int>>& snake) {
	int rows = field.size();
	int cols = field[0].size();

	while (true) {
		headX = (rows - 2) / 2 + 1;
		headY = (cols - 2) / 2 + 1;
		if (field[headX][headY] != '1') {
			snake.push_back({ headX, headY });
			field[headX][headY] = 'O';
			break;
		}
	}
}

void dynamicSpeed(int& snakeLength) {
	if (snakeLength < 4) sp = fourth;
	else if (snakeLength >= 4 && snakeLength < 10) sp = third;
	else if (snakeLength >= 10 && snakeLength < 14) sp = add;
	else if (snakeLength >= 14 && snakeLength < 20) sp = second;
	else if (snakeLength >= 20) sp = first;
}

void speedDirection(int& snakeLength) {
	switch (input) {
	case '1': sp = first; break;
	case '2': sp = second; break;
	case '3': sp = third; break;
	case '4': sp = fourth; break;
	case '5': dynamicSpeed(snakeLength);
	}
}

void averageWindow(sf::RenderWindow& window, int& offsetX, int& offsetY) {
	int fieldWidth = cols * cellSize;
	int fieldHeight = rows * cellSize;

	sf::Vector2u windowSize = window.getSize();

	offsetX = (windowSize.x - fieldWidth) / 2;
	offsetY = (windowSize.y - fieldHeight) / 2;
}

void coundScore(sf::RenderWindow& window, int& snakeLength, sf::Font& font, std::vector<std::vector<char>>& field, int& offsetX, int& offsetY) {
	int rows = field.size();
	int cols = field[0].size();

	sf::Text text;
	text.setFont(font);
	text.setString("Score: " + std::to_string(snakeLength));
	text.setCharacterSize(36);
	text.setFillColor(sf::Color(255, 250, 205));
	text.setStyle(sf::Text::Bold);

	sf::FloatRect textRect = text.getGlobalBounds();

	text.setPosition(static_cast<float>(offsetX + (cols * cellSize - textRect.width) / 2), 
					 static_cast<float>(offsetY + rows * cellSize - textRect.height - 134));

	window.draw(text);
}

void chooseStyleOnce() {
	if (!isStyleChosen) {
		styleChooce();
		isStyleChosen = true;
	}
}

void textureSnake(sf::RenderWindow& window, std::vector<std::pair<int, int>>& snake, int& offsetX, int& offsetY) {

	chooseStyleOnce();

	std::vector<std::pair<int, int>> headPosition;

	for (size_t i = 0; i < snake.size(); ++i) {
		sf::Sprite spriteBody;
		sf::Sprite spriteHead;
		int xCurr = snake[i].first;
		int yCurr = snake[i].second;

		if (i == 0) {
			int xNext = snake[i + 1].first;
			int yNext = snake[i + 1].second;

			int deltaX = xNext - xCurr;
			int deltaY = yNext - yCurr;

			headPosition.push_back({ deltaX, deltaY });

			if (headPosition[0] == std::make_pair(0, -1)) {
				spriteHead.setTexture(headRight);
				headPosition.pop_back();
			}
			else if (headPosition[0] == std::make_pair(-1, 0)) {
				spriteHead.setTexture(headDown);
				headPosition.pop_back();
			}
			else if (headPosition[0] == std::make_pair(0, 1)) {
				spriteHead.setTexture(headLeft);
				headPosition.pop_back();
			}
			else if (headPosition[0] == std::make_pair(1, 0)) {
				spriteHead.setTexture(headUp);
				headPosition.pop_back();
			}

			spriteHead.setScale(static_cast<float>(cellSize) / headUp.getSize().x,
								static_cast<float>(cellSize) / headUp.getSize().y);
			spriteHead.setPosition(static_cast<float>(snake[i].second * cellSize + offsetX), static_cast<float>(snake[i].first * cellSize + offsetY - 120));
			window.draw(spriteHead);
		}
		else if (i == snake.size() - 1) {
			sf::Sprite spriteTail;

			int xPrev = snake[i - 1].first;
			int yPrev = snake[i - 1].second;
			int xNext = snake[i + 1].first;
			int yNext = snake[i + 1].second;

			if (yPrev == yNext && xPrev < xNext) {
				spriteTail.setTexture(tailUp); 
			}
			else if (yPrev == yNext && xPrev > xNext) {
				spriteTail.setTexture(tailDown);
			}
			else if (xPrev == xNext && yPrev > yNext) {
				spriteTail.setTexture(tailRight);
			}
			else if (xPrev == xNext && yPrev < yNext) {
				spriteTail.setTexture(tailLeft);
			}

			float scaleXT = static_cast<float>(cellSize) / tailUp.getSize().x;
			float scaleYT = static_cast<float>(cellSize) / tailUp.getSize().y;
			spriteTail.setScale(scaleXT, scaleYT);
			spriteTail.setPosition(static_cast<float>(snake[i].second * cellSize + offsetX), static_cast<float>(snake[i].first * cellSize + offsetY - 120));
			window.draw(spriteTail);
			continue;
		}
		else {
			int xPrev = snake[i - 1].first;
			int yPrev = snake[i - 1].second;
			int xNext = snake[i + 1].first;
			int yNext = snake[i + 1].second;

			int previosX = xNext - xCurr;
			int previosY = yNext - yCurr;

			int nextX = xPrev - xCurr;
			int nextY = yPrev - yCurr;

			if (xPrev == xNext) {
				spriteBody.setTexture(bodyHorizontal);
			}
			else if (yPrev == yNext) {
				spriteBody.setTexture(bodyVertical);
			}
			else {
				if ((nextX == 1 && previosY == 1) || (nextY == 1 && previosX == 1)) {
					std::cout << "Applying texture: rightUp\n";
					spriteBody.setTexture(rightUp);
				}
				else if ((nextY == 1 && previosX == -1) || (nextX == -1 && previosY == 1)) {
					std::cout << "Applying texture: rightDown\n";
					spriteBody.setTexture(rightDown);
				}
				else if ((nextY == -1 && previosX == 1) || (nextX == 1 && previosY == -1)) {
					std::cout << "Applying texture: leftUp\n";
					spriteBody.setTexture(leftUp);
				}
				else if ((nextX == -1 && previosY == -1) || (nextY == -1 && previosX == -1)) {
					std::cout << "Applying texture: leftDown\n";
					spriteBody.setTexture(leftDown);
				}
			}

			if (!spriteBody.getTexture()) {
				std::cerr << RED_TEXT << "Error: Texture not set correctly for body segment\n"
					<< "Coordinates: (" << xCurr << ", " << yCurr << ")\n"
					<< "Previous: (" << xPrev << ", " << yPrev << "), Next: (" << xNext << ", " << yNext << ")\n"
					<< RESET_TEXT;
				continue;
			}

			spriteBody.setScale(static_cast<float>(cellSize) / spriteBody.getTexture()->getSize().x,
								static_cast<float>(cellSize) / spriteBody.getTexture()->getSize().y);
			spriteBody.setPosition(static_cast<float>(yCurr * cellSize + offsetX), static_cast<float>(xCurr * cellSize + offsetY - 120));
			window.draw(spriteBody);
		}
	}
}

void draw(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake, int& offsetX, int& offsetY) {

	fieldChoose(window, field, snake, offsetX, offsetY);

}

void startGame(gameState& state) {
	sf::RenderWindow start(sf::VideoMode(1920, 1080), "Settings", sf::Style::Fullscreen);

	Cursor::setCostumCursor(start, "backgroundTexture/hand.png");

	sf::Font font;
	if (!font.loadFromFile("font/ArcadeClassic.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture textureBack;
	if (!textureBack.loadFromFile("backgroundTexture/menuTextureBackground7.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}
	
	sf::Sprite background;
	background.setTexture(textureBack);

	sf::Texture buttonBackNormal;
	if (!buttonBackNormal.loadFromFile("backgroundTexture/layer3.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonBackClick;
	if (!buttonBackClick.loadFromFile("backgroundTexture/layer4.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture textureBackSecond;
	if (!textureBackSecond.loadFromFile("backgroundTexture/monitorMain1.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Sprite backgroundSecond;
	backgroundSecond.setTexture(textureBackSecond);

	sf::Vector2u startSize = start.getSize();
	std::cout << startSize.x << " " << startSize.y;
	backgroundSecond.setTextureRect(sf::IntRect(0, 0, startSize.x, startSize.y));

	sf::Text speedLabel("Choose   Speed", font, 80);
	speedLabel.setFillColor(sf::Color::White);
	speedLabel.setOutlineThickness(3.0f);
	speedLabel.setPosition(710, 125);

	Button first("quickly", { 300, 100 }, 65, sf::Color::White);
	first.setFont(font);
	first.setTexture(buttonBackNormal);
	first.setTextOutline(2.0f);
	first.setTextStyle();
	first.setPosition({ 720, 320 });
	first.setOrigin({ 150, 45 });

	Button second("fast", { 300, 100 }, 65, sf::Color::White);
	second.setFont(font);
	second.setTexture(buttonBackNormal);
	second.setTextOutline(2.0f);
	second.setTextStyle();
	second.setPosition({ 1180, 320 });
	second.setOrigin({ 150, 45 });

	Button third("medium", { 300, 100 }, 65, sf::Color::White);
	third.setFont(font);
	third.setTexture(buttonBackNormal);
	third.setTextOutline(2.0f);
	third.setTextStyle();
	third.setPosition({ 720, 500 });
	third.setOrigin({ 150, 45 });

	Button fourth("slow", { 300, 100 }, 65, sf::Color::White);
	fourth.setFont(font);
	fourth.setTexture(buttonBackNormal);
	fourth.setTextOutline(2.0f);
	fourth.setTextStyle();
	fourth.setPosition({ 1180, 500 });
	fourth.setOrigin({ 150, 45 });

	Button dynamic("dynamic", { 300, 100 }, 65, sf::Color::White);
	dynamic.setFont(font);
	dynamic.setTexture(buttonBackNormal);
	dynamic.setTextOutline(2.0f);
	dynamic.setTextStyle();
	dynamic.setPosition({ 960, 670 });
	dynamic.setOrigin({ 150, 45 });

	float startWidth = rows * cellSize;
	float startHeight = cols * cellSize;

	sf::Vector2u startWindow = start.getSize();

	float offX = (startWindow.x - startWidth) / 2.0f;
	float offY = (startWindow.y - startHeight) / 2.0f;

	background.setPosition({offX - 90, offY - 25});

	int currentField = 0;

	while(start.isOpen()){
		sf::Event event;
		while (start.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {

					if (first.mousePosition(start)) {
						first.setPressed(true);
						first.textureUpdate(start, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (second.mousePosition(start)) {
						second.setPressed(true);
						second.textureUpdate(start, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (third.mousePosition(start)) {
						third.setPressed(true);
						third.textureUpdate(start, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (fourth.mousePosition(start)) {
						fourth.setPressed(true);
						fourth.textureUpdate(start, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (dynamic.mousePosition(start)) {
						dynamic.setPressed(true);
						dynamic.textureUpdate(start, buttonBackClick, buttonBackNormal);
						soundBotton();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (first.getPressed()) {
						first.setPressed(false);
						first.textureUpdate(start, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(100));
						input = '1';
						std::cout << "Input value: " << input << std::endl;
						start.close();
					}
					else if (second.getPressed()) {
						second.setPressed(false);
						second.textureUpdate(start, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(100));
						input = '2';
						start.close();
					}
					else if (third.getPressed()) {
						third.setPressed(false);
						third.textureUpdate(start, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(100));
						input = '3';
						start.close();
					}
					else if (fourth.getPressed()) {
						fourth.setPressed(false);
						fourth.textureUpdate(start, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(100));
						input = '4';
						start.close();
					}
					else if (dynamic.getPressed()) {
						dynamic.setPressed(false);
						dynamic.textureUpdate(start, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(100));
						input = '5';
						start.close();
					}
				}
			}

			first.update(start);
			second.update(start);
			third.update(start);
			fourth.update(start);
			dynamic.update(start);

			start.clear();

			start.draw(backgroundSecond);
			start.draw(background);
			start.draw(speedLabel);

			first.drawTo(start);
			second.drawTo(start);
			third.drawTo(start);
			fourth.drawTo(start);
			dynamic.drawTo(start);

			start.display();
		}
	}
	state = GAME;
}

void style(gameState& state, int page = 1) {
	while (true) {
		sf::RenderWindow styleWindow(sf::VideoMode(1920, 1080), "Settings", sf::Style::Fullscreen);

		Cursor::setCostumCursor(styleWindow, "backgroundTexture/hand.png");

		sf::Texture backgroundSecond;
		if (!backgroundSecond.loadFromFile("backgroundTexture/monitorMain1.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture backgroundFirst;
		if (!backgroundFirst.loadFromFile("style/styleBack.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture buttonBackNormal;
		if (!buttonBackNormal.loadFromFile("backgroundTexture/layer3.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture buttonBackClick;
		if (!buttonBackClick.loadFromFile("backgroundTexture/layer4.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture styleFirst, styleSecond, styleThird, styleFourth;
		if (page == 1) {
			styleFirst.loadFromFile("style/style1.png");
			styleSecond.loadFromFile("style/style2.png");
			styleThird.loadFromFile("style/style3.png");
			styleFourth.loadFromFile("style/style4.png");
		}
		else if (page == 2) {
			styleFirst.loadFromFile("style/style5.png");
			styleSecond.loadFromFile("style/style6.png");
			styleThird.loadFromFile("style/style7.png");
			styleFourth.loadFromFile("style/style8.png");
		}
		else if (page == 3) {
			break;
		}

		displayStyleWindow(styleWindow, state, backgroundFirst, backgroundSecond, styleFirst, styleSecond, styleThird, styleFourth, buttonBackNormal, buttonBackClick, page);
		
		if (state != STYLE) {
			break;
		}
	}
}

void endGame(int& snakeLength, gameState& state) {
	sf::Font font;
	if (!font.loadFromFile("font/ArcadeClassic.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	sf::RenderWindow end(sf::VideoMode(1920, 1080), "End", sf::Style::Fullscreen);

	Cursor::setCostumCursor(end, "backgroundTexture/hand.png");

	sf::Texture textureBackSecond;
	if (!textureBackSecond.loadFromFile("backgroundTexture/monitorMain1.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Sprite backgroundSecond;
	backgroundSecond.setTexture(textureBackSecond);

	sf::Vector2u endSize = end.getSize();
	std::cout << endSize.x << " " << endSize.y;
	backgroundSecond.setTextureRect(sf::IntRect(0, 0, endSize.x, endSize.y));

	sf::Texture textureBack;
	if (!textureBack.loadFromFile("backgroundTexture/menuTextureBackground7.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Sprite background;
	background.setTexture(textureBack);

	sf::Texture buttonBackNormal;
	if (!buttonBackNormal.loadFromFile("backgroundTexture/layer3.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonBackClick;
	if (!buttonBackClick.loadFromFile("backgroundTexture/layer4.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Text text;
	text.setFont(font);
	if (win) {
		text.setString("You\n\nWIN!");
		text.setCharacterSize(150);
	}
	else if (!win){
		text.setString("Game Over!\n\n    Score   " + std::to_string(snakeLength));
	}
	text.setCharacterSize(90);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(3.0f);
	text.setStyle(sf::Text::Bold);
	sf::FloatRect textBounds = text.getGlobalBounds();
	text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
	text.setPosition(970, 280);

	float startWidth = rows * cellSize;
	float startHeight = cols * cellSize;

	sf::Vector2u endWindow = end.getSize();

	float offX = (endWindow.x - startWidth) / 2.0f;
	float offY = (endWindow.y - startHeight) / 2.0f;

	background.setPosition({ offX - 90, offY - 25 });

	Button restart("Restart", { 300, 100 }, 65, sf::Color::White);
	restart.setFont(font);
	restart.setTexture(buttonBackNormal);
	restart.setTextOutline(2.0f);
	restart.setTextStyle();
	restart.setPosition({ 770, 620 });
	restart.setOrigin({ 150, 45 });

	Button menu("Menu", { 300, 100 }, 65, sf::Color::White);
	menu.setFont(font);
	menu.setTexture(buttonBackNormal);
	menu.setTextOutline(2.0f);
	menu.setTextStyle();
	menu.setPosition({ 1160, 620 });
	menu.setOrigin({ 150, 45 });
	
	while (end.isOpen()) {
		sf::Event event;
		while (end.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {

					if (restart.mousePosition(end)) {
						restart.setPressed(true);
						restart.textureUpdate(end, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (menu.mousePosition(end)) {
						menu.setPressed(true);
						menu.textureUpdate(end, buttonBackClick, buttonBackNormal);
						soundBotton();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (restart.getPressed()) {
						restart.setPressed(false);
						restart.textureUpdate(end, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(100));
						checkEnd = false;
						end.close();
						endMusic.stop();
					}
					else if (menu.getPressed()) {
						menu.setPressed(false);
						menu.textureUpdate(end, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(100));
						checkEnd = true;
						end.close();
						endMusic.stop();
					}
				}
			}
		}

		restart.update(end);
		menu.update(end);

		end.clear();

		end.draw(backgroundSecond);
		end.draw(background);
		end.draw(text);

		restart.drawTo(end);
		menu.drawTo(end);

		end.display();
	}
}

void loadRecords(int& firstRecord, int& secondRecord, int& thirdRecord, int& fourthRecord, int& dynamicRecord) {
	std::ifstream file("record.txt");
	if (file.is_open()) {
		file >> firstRecord >> secondRecord >> thirdRecord >> fourthRecord >> dynamicRecord;
		file.close();
	}
	else {
		firstRecord = secondRecord = thirdRecord = fourthRecord = dynamicRecord = 0;
	}
}

void saveRecords(int firstRecord, int secondRecord, int thirdRecord, int fourthRecord, int dynamicRecord) {
	std::ofstream file("record.txt");
	if (file.is_open()) {
		file << firstRecord << std::endl;
		file << secondRecord << std::endl;
		file << thirdRecord << std::endl;
		file << fourthRecord << std::endl;
		file << dynamicRecord << std::endl;
		file.close();
	}
}

void timeArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField, int& offsetX, int& offsetY) {
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	int rows = thirdField.size();
	int cols = thirdField[0].size();

	textTime.setFont(font);
	textTime.setCharacterSize(36);
	textTime.setFillColor(sf::Color(255, 250, 205));
	textTime.setStyle(sf::Text::Bold);

	int elapsedTime = timeLevel - levelTimer.getElapsedTime().asSeconds();
	if (elapsedTime < 0) elapsedTime = 0;

	textTime.setString("Time: " + std::to_string(elapsedTime));

	sf::FloatRect textRect = textTime.getGlobalBounds();

	textTime.setPosition(static_cast<float>(offsetX + (cols * cellSize - textRect.width) / 2),
						 static_cast<float>(offsetY + (rows * cellSize - textRect.height - 924) / 2));

	window.draw(textTime);
}

void scoreArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField, int& offsetX, int& offsetY) {
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	int rows = thirdField.size();
	int cols = thirdField[0].size();

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

void startText(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField, int& offsetX, int& offsetY) {
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	int rows = thirdField.size();
	int cols = thirdField[0].size();

	sf::Text textStart;
	textStart.setString("   Press any key\n to start the game");
	textStart.setFont(font);
	textStart.setCharacterSize(36);
	textStart.setFillColor(sf::Color(255, 250, 205));
	textStart.setStyle(sf::Text::Bold);

	sf::FloatRect textRect = textStart.getGlobalBounds();

	textStart.setPosition(static_cast<float>(offsetX + (cols * cellSize - textRect.width) / 2),
						  static_cast<float>(offsetY + (rows * cellSize - textRect.height - 200) / 2));

	window.draw(textStart);
}

void startGameWithSettings(int& headX, int& headY, int& offsetX, int& offsetY, gameState& state, int& firstRecord, int& secondRecord, int& thirdRecord, int& fourthRecord, int& dynamicRecord) {
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Snake Game", sf::Style::Fullscreen);
	averageWindow(window, offsetX, offsetY);

	window.setMouseCursorVisible(false);

	sf::Texture textureBackSecond;
	if (!textureBackSecond.loadFromFile("backgroundTexture/monitorMain1.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Sprite backgroundSecond;
	backgroundSecond.setTexture(textureBackSecond);

	sf::Vector2u windowSize = window.getSize();
	std::cout << windowSize.x << " " << windowSize.y;
	backgroundSecond.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));

	std::vector<std::vector<char>> field = barier();
	std::vector<std::pair<int, int>> snake;

	switch (inputArcad) {
	case '1':
		field = firstField();
		break;
	case '2':
		field = secondField();
		break;
	case '3':
		field = thirdField();
		break;
	default:
		field = barier();
		break;
	}

	mainSound();

	if (inputArcad != '3') {
		speedDirection(snakeLength);
	}
	startPosition(field, headX, headY, snake);
	food(field);

	while (!startKey && window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			window.clear();

			window.draw(backgroundSecond);
			draw(window, field, snake, offsetX, offsetY);
			startText(window, field, offsetX, offsetY);
			if (event.type == sf::Event::KeyPressed) {
				startKey = true;
				sf::sleep(sf::milliseconds(250));
				levelTimer.restart();
				window.close();
				break;
			}

			window.display();
		}
	}

	while (window.isOpen()) {
		sf::Event event;
		bool directionChanged = false;
		while (window.pollEvent(event)) {
			if (input == '5') {
				dynamicSpeed(snakeLength);
			}

			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && !directionChanged) {
				switch (event.key.code) {
				case sf::Keyboard::A:
				case sf::Keyboard::Left:
					if (dir != right) {
						dir = left;
						directionChanged = true;
					}
					break; 
				case sf::Keyboard::D:
				case sf::Keyboard::Right:
					if (dir != left) {
						dir = right;
						directionChanged = true;
					}
					break;
				case sf::Keyboard::W:
				case sf::Keyboard::Up:
					if (dir != down) {
						dir = up;
						directionChanged = true;
					}
					break;
				case sf::Keyboard::S:
				case sf::Keyboard::Down:
					if (dir != up) {
						dir = down;
						directionChanged = true;
					}
					break;
				}
			}
		}

		if (state == GAME && startKey) {

			chooceArcad(window, headX, headY, snakeLength, state, field, snake, offsetX, offsetY);

			directionChanged = false;

			window.clear();

			window.draw(backgroundSecond);
			draw(window, field, snake, offsetX, offsetY);
			textureSnake(window, snake, offsetX, offsetY);
			
			if (inputArcad == '3') {
				timeArcad(window, field, offsetX, offsetY);
				scoreArcad(window, field, offsetX, offsetY);
			}
			else {
				coundScore(window, snakeLength, font, field, offsetX, offsetY);
			}

			window.display();
			sf::sleep(sf::milliseconds(sp));
		}
		else {
			if (input == '1') {
				firstRecord = std::max(firstRecord, snakeLength);
			}
			else if (input == '2') {
				secondRecord = std::max(secondRecord, snakeLength);
			}
			else if (input == '3') {
				thirdRecord = std::max(thirdRecord, snakeLength);
			}
			else if (input == '4') {
				fourthRecord = std::max(fourthRecord, snakeLength);
			}
			else if (input == '5') {
				dynamicRecord = std::max(dynamicRecord, snakeLength);
			}

			break;
		}
	}
	music.stop();
}

void recordMenu(gameState& state, int& firstRecord, int& secondRecord, int& thirdRecord, int& fourthRecord, int& dynamicRecord) {
	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Font fontButton;
	if (!fontButton.loadFromFile("font/ArcadeClassic.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	sf::RenderWindow record(sf::VideoMode(1920, 1080), "Record", sf::Style::Fullscreen);

	Cursor::setCostumCursor(record, "backgroundTexture/hand.png");

	sf::Texture textureBack;
	if (!textureBack.loadFromFile("backgroundTexture/monitorMain1.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Sprite background;
	background.setTexture(textureBack);

	sf::Vector2u recordSize = record.getSize();
	background.setTextureRect(sf::IntRect(0, 0, recordSize.x, recordSize.y));

	sf::Texture textureBackSecond;
	if (!textureBackSecond.loadFromFile("backgroundTexture/menuTextureBackground7.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Sprite backgroundSecond;
	backgroundSecond.setTexture(textureBackSecond);

	float styleWidth = rows * cellSize;
	float styleHeight = cols * cellSize;

	float offX = (recordSize.x - styleWidth) / 2.0f;
	float offY = (recordSize.y - styleHeight) / 2.0f;

	backgroundSecond.setPosition({ offX - 90, offY - 25 });

	sf::Texture buttonBackNormal;
	if (!buttonBackNormal.loadFromFile("backgroundTexture/layer3.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonBackClick;
	if (!buttonBackClick.loadFromFile("backgroundTexture/layer4.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	Button menu("menu", { 300, 100 }, 65, sf::Color::White);
	menu.setFont(fontButton);
	menu.setTextStyle();
	menu.setTextOutline(2.0f);
	menu.setTexture(buttonBackNormal);
	menu.setPosition({recordSize.x / 2.0f, 840});
	menu.setOrigin({ 150, 45 });

	sf::Text first;
	first.setFont(font);
	first.setString(" Quickly\nScore: " + std::to_string(firstRecord));
	first.setCharacterSize(65);
	first.setFillColor(sf::Color::White);
	first.setOutlineThickness(3.0f);
	first.setStyle(sf::Text::Bold);
	first.setPosition(620, 150);

	sf::Text second;
	second.setFont(font);
	second.setString("  Fast\nScore: " + std::to_string(secondRecord));
	second.setCharacterSize(65);
	second.setFillColor(sf::Color::White);
	second.setOutlineThickness(3.0f);
	second.setStyle(sf::Text::Bold);
	second.setPosition(1060, 150);

	sf::Text third;
	third.setFont(font);
	third.setString(" Medium\nScore: " + std::to_string(thirdRecord));
	third.setCharacterSize(65);
	third.setFillColor(sf::Color::White);
	third.setOutlineThickness(3.0f);
	third.setStyle(sf::Text::Bold);
	third.setPosition(620, 390);

	sf::Text fourth;
	fourth.setFont(font);
	fourth.setString("  Slow\nScore: " + std::to_string(fourthRecord));
	fourth.setCharacterSize(65);
	fourth.setFillColor(sf::Color::White);
	fourth.setOutlineThickness(3.0f);
	fourth.setStyle(sf::Text::Bold);
	fourth.setPosition(1060, 390);

	sf::Text dynamic;
	dynamic.setFont(font);
	dynamic.setString("Dynamic\nScore: " + std::to_string(dynamicRecord));
	dynamic.setCharacterSize(65);
	dynamic.setFillColor(sf::Color::White);
	dynamic.setOutlineThickness(3.0f);
	dynamic.setStyle(sf::Text::Bold);
	dynamic.setPosition(840, 590);

	while (record.isOpen()) {
		sf::Event event;
		while (record.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (menu.mousePosition(record)) {
						menu.setPressed(true);
						menu.textureUpdate(record, buttonBackClick, buttonBackNormal);
						soundBotton();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (menu.getPressed()) {
						menu.setPressed(false);
						menu.textureUpdate(record, buttonBackClick, buttonBackNormal);
						soundBotton();
						record.close();
						state = MENU;
					}
				}
			}

			menu.update(record);

			record.clear();

			record.draw(background);
			record.draw(backgroundSecond);

			record.draw(first);
			record.draw(second);
			record.draw(third);
			record.draw(fourth);
			record.draw(dynamic);

			menu.drawTo(record);

			record.display();
		}
	}

}

void arcad(gameState& state, int page = 1) {
	while (true) {
		sf::RenderWindow ArcadWindow(sf::VideoMode(1920, 1080), "Arcad", sf::Style::Fullscreen);

		Cursor::setCostumCursor(ArcadWindow, "backgroundTexture/hand.png");

		sf::Texture backgroundSecond;
		if (!backgroundSecond.loadFromFile("backgroundTexture/monitorMain1.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture backgroundFirst;
		if (!backgroundFirst.loadFromFile("style/styleBack.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture buttonBackNormal;
		if (!buttonBackNormal.loadFromFile("backgroundTexture/layer3.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture buttonBackClick;
		if (!buttonBackClick.loadFromFile("backgroundTexture/layer4.png")) {
			std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
			return;
		}

		sf::Texture styleFirst, styleSecond, styleThird, styleFourth;
		if (page == 1) {
			styleFirst.loadFromFile("style/arcad1.png");
			styleSecond.loadFromFile("style/arcad2.png");
			styleThird.loadFromFile("style/arcad3.png");
			styleFourth.loadFromFile("style/arcad.png");
		}
		else if (page == 2) {
			styleFirst.loadFromFile("style/arcad.png");
			styleSecond.loadFromFile("style/arcad.png");
			styleThird.loadFromFile("style/arcad.png");
			styleFourth.loadFromFile("style/arcad.png");
		}
		else if (page == 3) {
			break;
		}

		displayArcadWindow(ArcadWindow, state, backgroundFirst, backgroundSecond, styleFirst, styleSecond, styleThird, styleFourth, buttonBackNormal, buttonBackClick, page);

		if (state != ARCAD) {
			break;
		}
	}
}

void menuBar(sf::RenderWindow& menu, int& headX, int& headY, int& offsetX, int& offsetY, gameState& state) {	
	sf::Font font;
	if (!font.loadFromFile("font/ArcadeClassic.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return;
	}

	Cursor::setCostumCursor(menu, "backgroundTexture/hand.png");

	sf::Texture textureBack;
	if (!textureBack.loadFromFile("backgroundTexture/menuTextureBackground5.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Sprite background;
	background.setTexture(textureBack);

	sf::Texture buttonBackNormal;
	if (!buttonBackNormal.loadFromFile("backgroundTexture/layer3.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonBackClick;
	if (!buttonBackClick.loadFromFile("backgroundTexture/layer4.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonFullSoundNormal;
	if(!buttonFullSoundNormal.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon1.png")){
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonFullSoundClick;
	if (!buttonFullSoundClick.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon12.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonNullSoundNormal;
	if (!buttonNullSoundNormal.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon2.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Texture buttonNullSoundClick;
	if (!buttonNullSoundClick.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon21.png")) {
		std::cerr << RED_TEXT << "Error loading image file" << RESET_TEXT << std::endl;
		return;
	}

	sf::Text title("Snake Game", font, 200);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setOutlineThickness(3.0f);
	sf::FloatRect titleBounds = title.getGlobalBounds();
	title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
	title.setPosition(960, 70);

	Button startTest("start", { 500, 130 }, 80, sf::Color::White);
	startTest.setFont(font);
	startTest.setTexture(buttonBackNormal);
	startTest.setTextOutline(3.0f);
	startTest.setTextStyle();
	startTest.setPosition({ 960, 310 });
	startTest.setOrigin({ 250, 60 });

	Button styleTest("style", {500, 130}, 80, sf::Color::White);
	styleTest.setFont(font);
	styleTest.setTexture(buttonBackNormal);
	styleTest.setTextOutline(3.0f);
	styleTest.setTextStyle();
	styleTest.setPosition({ 960, 470 });
	styleTest.setOrigin({ 250, 65 });

	Button arcadTest("arcad", { 500, 130 }, 80, sf::Color::White);
	arcadTest.setFont(font);
	arcadTest.setTexture(buttonBackNormal);
	arcadTest.setTextOutline(3.0f);
	arcadTest.setTextStyle();
	arcadTest.setPosition({ 960, 630 });
	arcadTest.setOrigin({ 250, 55 });

	Button recordTest("record", { 500, 130 }, 80, sf::Color::White);
	recordTest.setFont(font);
	recordTest.setTexture(buttonBackNormal);
	recordTest.setTextOutline(3.0f);
	recordTest.setTextStyle();
	recordTest.setPosition({ 960, 790 });
	recordTest.setOrigin({ 250, 55 });

	Button exitTest("exit", { 500, 130 }, 80, sf::Color::White);
	exitTest.setFont(font);
	exitTest.setTexture(buttonBackNormal);
	exitTest.setTextOutline(3.0f);
	exitTest.setTextStyle();
	exitTest.setPosition({ 960, 950 });
	exitTest.setOrigin({ 250, 60 });

	Button soundTest("sound", { 150, 130 }, 80, sf::Color::White);
	if (!checkSound) {
		soundTest.setTexture(buttonFullSoundNormal);
	}
	else {
		soundTest.setTexture(buttonNullSoundNormal);
	}
	soundTest.setPosition({ 1810, 990 });

	while (menu.isOpen()) {
		sf::Event event;
		while (menu.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {

					if (startTest.mousePosition(menu)) {
						startTest.setPressed(true);
						startTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (styleTest.mousePosition(menu)) {
						styleTest.setPressed(true);
						styleTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (arcadTest.mousePosition(menu)) {
						arcadTest.setPressed(true);
						arcadTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (recordTest.mousePosition(menu)) {
						recordTest.setPressed(true);
						recordTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (exitTest.mousePosition(menu)) {
						exitTest.setPressed(true);
						exitTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						soundBotton();
					}

					if (!checkSound) {
						if (soundTest.mousePosition(menu)) {
							soundTest.setPressed(true);
							soundTest.textureUpdate(menu, buttonNullSoundClick, buttonNullSoundNormal);
							soundBotton();
						}
					}
					if (checkSound) {
						if (soundTest.mousePosition(menu)) {
							soundTest.setPressed(true);
							soundTest.textureUpdate(menu, buttonFullSoundClick, buttonFullSoundNormal);
							soundBotton();
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (startTest.getPressed()) {
						startTest.setPressed(false);
						startTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						state = START;
						return;
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (styleTest.getPressed()) {
						styleTest.setPressed(false);
						styleTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						state = STYLE;
						return;
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (arcadTest.getPressed()) {
						arcadTest.setPressed(false);
						arcadTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						state = ARCAD;
						return;
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (recordTest.getPressed()) {
						recordTest.setPressed(false);
						recordTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						state = RECORD;
						return;
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (exitTest.getPressed()) {
						exitTest.setPressed(false);
						exitTest.textureUpdate(menu, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						menu.close();
					}
				}
			}

			if (!checkSound) {
				if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (soundTest.getPressed()) {
							soundTest.setPressed(false);
							soundTest.textureUpdate(menu, buttonNullSoundClick, buttonNullSoundNormal);
							sf::sleep(sf::milliseconds(120));
							soundTest.setTexture(buttonNullSoundNormal);
							checkSound = true;
						}
					}
				}
			}

			if (checkSound) {
				if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						if (soundTest.getPressed()) {
							soundTest.setPressed(false);
							soundTest.textureUpdate(menu, buttonFullSoundClick, buttonFullSoundNormal);
							sf::sleep(sf::milliseconds(120));
							soundTest.setTexture(buttonFullSoundNormal);
							checkSound = false;
						}
					}
				}
			}

			startTest.update(menu);
			styleTest.update(menu);
			arcadTest.update(menu);
			recordTest.update(menu);
			exitTest.update(menu);
			soundTest.update(menu);

			menu.clear();

			menu.draw(background);

			menu.draw(title);
			
			startTest.drawTo(menu);
			styleTest.drawTo(menu);
			arcadTest.drawTo(menu);
			recordTest.drawTo(menu);
			exitTest.drawTo(menu);
			soundTest.drawTo(menu);

			menu.display();
		}
	}
}

int main() {
	srand(time(NULL));

	int headX, headY;
	int offsetX = 0;
	int offsetY = 0;

	int firstRecord;
	int secondRecord;
	int thirdRecord;
	int fourthRecord;
	int dynamicRecord;

	loadRecords(firstRecord, secondRecord, thirdRecord, fourthRecord, dynamicRecord);

	sf::Font font;
	if (!font.loadFromFile("font/arial.ttf")) {
		std::cerr << RED_TEXT << "Error loading font file" << RESET_TEXT << std::endl;
		return 0;
	}

	sf::RenderWindow menu(sf::VideoMode(1920, 1080), "Menu", sf::Style::Fullscreen);

	gameState state = MENU;

	while (menu.isOpen()) {

		menu.clear();

		switch (state)
		{
		case MENU:
			menuBar(menu, headX, headY, offsetX, offsetY, state);
			break;
		case START:
			if (!checkButton)
				inputStyle = '1';
			startGame(state);
			break;
		case STYLE:
			style(state);
			break;
		case ARCAD:
			arcad(state);
			break;
		case RECORD:
			recordMenu(state, firstRecord, secondRecord, thirdRecord, fourthRecord, dynamicRecord);
			break;
		case GAME:
			startGameWithSettings(headX, headY, offsetX, offsetY, state, firstRecord, secondRecord, thirdRecord, fourthRecord, dynamicRecord);
			break;
		case END:
			endGame(snakeLength, state);

			foodIndex = 0;

			if (!checkEnd) {
				state = GAME;
				snakeLength = 1;
				headX = 0;
				headY = 0;

				if (inputArcad == '3') {
					timeLevel = 25;
					levelTimer.restart();
					sp = third;
					win = false;
				}
				startKey = false;
			}
			else {
				snakeLength = 1;
				isStyleChosen = false;
				checkButton = false;
				headX = 0;
				headY = 0;

				inputArcad = ' ';
				win = false;
				startKey = false;
				state = MENU;
			}
			break;
		}

		menu.display();
	}

	saveRecords(firstRecord, secondRecord, thirdRecord, fourthRecord, dynamicRecord);

	return 0;
}