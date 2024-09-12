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
#include "Texture.h"
#include "Font.h"
#include "ButtonView.h"
#include "Fade.h"

#include "Arcad1.h"
#include "Arcad2.h"
#include "Arcad3.h"
#include "Arcad4.h"

#define RED_TEXT "\033[1;31m"
#define WHITE_TEXT "\033[1;37m"
#define PURPLE_TEXT "\033[1;35m"
#define YELLOW_TEXT "\033[1;33m"
#define BLUE_TEXT "\033[0;94m"

#define RESET_TEXT "\033[0m"

std::vector<std::vector<char>> barier() {
	std::vector<std::vector<char>> box(rows);

	box[0] = std::vector<char>(cols, '1');
	box[static_cast<size_t>(rows) - 1] = std::vector<char>(cols, '1');

	for (int i = 1; i < rows - 1; ++i) {
		box[i] = std::vector<char>(cols, ' ');
		box[i][0] = '1';
		box[i][static_cast<size_t>(cols) - 1] = '1';
	}

	return box;
}

void startPosition(std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {
	size_t rows = field.size();
	size_t cols = field[0].size();

	while (true) {
		headX = static_cast<int>((rows - 2) / 2 + 1);
		headY = static_cast<int>((cols - 2) / 2 + 1);
		if (field[headX][headY] != '1') {
			snake.push_back({ headX, headY });
			field[headX][headY] = 'O';
			break;
		}
	}
}

//ther (next four function) require moving to a separate file. 
void dynamicSpeed() {
	if (snakeLength < 4) sp = fourth;
	else if (snakeLength >= 4 && snakeLength < 10) sp = third;
	else if (snakeLength >= 10 && snakeLength < 14) sp = add;
	else if (snakeLength >= 14 && snakeLength < 20) sp = second;
	else if (snakeLength >= 20) sp = first;
}

void speedDirection() {
	switch (input) {
	case '1': sp = first; break;
	case '2': sp = second; break;
	case '3': sp = third; break;
	case '4': sp = fourth; break;
	case '5': dynamicSpeed();
	}
}

void averageWindow(sf::RenderWindow& window) {
	int fieldWidth = cols * cellSize;
	int fieldHeight = rows * cellSize;

	sf::Vector2u windowSize = window.getSize();

	offsetX = (windowSize.x - fieldWidth) / 2;
	offsetY = (windowSize.y - fieldHeight) / 2;
}

void coundScore(sf::RenderWindow& window, std::vector<std::vector<char>>& field) {
	size_t rows = field.size();
	size_t cols = field[0].size();

	sf::Text text;
	text.setFont(fontMain);
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

void textureSnake(sf::RenderWindow& window, std::vector<std::pair<int, int>>& snake) {

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

void draw(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {
	fieldChoose(window, field, snake);
}

void startGame(gameState& state) {
	sf::RenderWindow start(sf::VideoMode(1920, 1080), "Settings", sf::Style::Fullscreen);

	Cursor::setCostumCursor(start, "backgroundTexture/hand.png");

	sf::Sprite background;
	background.setTexture(backgroundSecond);

	sf::Vector2u startSize = start.getSize();
	background.setTextureRect(sf::IntRect(0, 0, startSize.x, startSize.y));
	
	sf::Sprite backgroundSecond;
	backgroundSecond.setTexture(textureBackSecond);

	sf::Vector2u startWindow = start.getSize();
	float startWidth = static_cast<float>(rows) * static_cast<float>(cellSize);
	float startHeight = static_cast<float>(cols) * static_cast<float>(cellSize);

	float offX = (startWindow.x - startWidth) / 2.0f;
	float offY = (startWindow.y - startHeight) / 2.0f;

	backgroundSecond.setPosition({ offX - 90, offY - 25 });

	sf::Text speedLabel("Choose   Speed", fontPixel, 80);
	speedLabel.setFillColor(sf::Color::White);
	speedLabel.setOutlineThickness(3.0f);
	speedLabel.setPosition(710, 125);

	std::vector<Button> buttons = {
		createSecondButton("quickly", buttonBackNormal, { 720, 320 }, { 150, 45 }),
		createSecondButton("fast", buttonBackNormal, { 1180, 320 }, { 150, 45 }),
		createSecondButton("medium", buttonBackNormal, { 720, 500 }, { 150, 45 }),
		createSecondButton("slow", buttonBackNormal, { 1180, 500 }, { 150, 45 }),
		createSecondButton("dynamic", buttonBackNormal, { 960, 670 }, { 150, 45 })
	};

	int currentField = 0;

	sf::RectangleShape blackScreen;
	int alpha;
	bool fadeOut = false;

	createParametrs(blackScreen, alpha);

	while(start.isOpen()){
		sf::Event event;
		while (start.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (size_t i = 0; i < buttons.size(); ++i) {
						if (buttons[i].mousePosition(start)) {
							buttons[i].setPressed(true);
							buttons[i].textureUpdate(start, buttonBackClick, buttonBackNormal);
							soundBotton();
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (size_t i = 0; i < buttons.size(); ++i) {
						if (buttons[i].getPressed()) {
							buttons[i].setPressed(false);
							buttons[i].textureUpdate(start, buttonBackClick, buttonBackNormal);
							sf::sleep(sf::milliseconds(100));

							if (i == 0) input = '1';
							if (i == 1) input = '2';
							if (i == 2) input = '3';
							if (i == 3) input = '4';
							if (i == 4) input = '5';

							fadeOut = true;
							state = GAME;
						}
					}
				}
			}
		}
		for (auto& i : buttons) {
			i.update(start);
		}

		start.clear();

		start.draw(background);
		start.draw(backgroundSecond);
		start.draw(speedLabel);

		for (auto& i : buttons) {
			i.drawTo(start);
		}

		settingFade(start, blackScreen, fadeOut, alpha, state);

		start.display();
	}
}

void style(gameState& state, int page = 1) {
	while (true) {
		sf::RenderWindow styleWindow(sf::VideoMode(1920, 1080), "Settings", sf::Style::Fullscreen);

		Cursor::setCostumCursor(styleWindow, "backgroundTexture/hand.png");

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

		displayStyleWindow(styleWindow, state, styleFirst, styleSecond, styleThird, styleFourth, page);
		
		if (state != STYLE) {
			break;
		}
	}
}

void endGame(gameState& state) {
	sf::RenderWindow end(sf::VideoMode(1920, 1080), "End", sf::Style::Fullscreen);

	Cursor::setCostumCursor(end, "backgroundTexture/hand.png");

	sf::Sprite background;
	background.setTexture(backgroundSecond);

	sf::Vector2u endSize = end.getSize();
	std::cout << endSize.x << " " << endSize.y;
	background.setTextureRect(sf::IntRect(0, 0, endSize.x, endSize.y));

	sf::Sprite backgroundSecond;
	backgroundSecond.setTexture(textureBackSecond);

	sf::Text text;
	text.setFont(fontPixel);
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

	float startWidth = static_cast<float>(rows) * static_cast<float>(cellSize);
	float startHeight = static_cast<float>(cols) * static_cast<float>(cellSize);

	sf::Vector2u endWindow = end.getSize();

	float offX = (endWindow.x - startWidth) / 2.0f;
	float offY = (endWindow.y - startHeight) / 2.0f;

	backgroundSecond.setPosition({ offX - 90, offY - 25 });

	std::vector<Button> buttons = {
		createSecondButton("Restart", buttonBackNormal, { 770, 620 }, { 150, 45 }),
		createSecondButton("Menu", buttonBackNormal, { 1160, 620 }, { 150, 45 })
	};
	
	sf::RectangleShape blackScreen;
	int alpha;
	bool fadeOut = false;

	createParametrs(blackScreen, alpha);

	while (end.isOpen()) {
		sf::Event event;
		while (end.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (size_t i = 0; i < buttons.size(); ++i) {
						if (buttons[i].mousePosition(end)) {
							buttons[i].setPressed(true);
							buttons[i].textureUpdate(end, buttonBackClick, buttonBackNormal);
							soundBotton();
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (size_t i = 0; i < buttons.size(); ++i) {
						if (buttons[i].getPressed()) {
							buttons[i].setPressed(false);
							buttons[i].textureUpdate(end, buttonBackClick, buttonBackNormal);
							sf::sleep(sf::milliseconds(100));
							
							if (i == 0) checkEnd = false;
							if (i == 1) checkEnd = true;

							fadeOut = true;
							endMusic.stop();
						}
					}
				}
			}
		}

		for (auto& i : buttons) {
			i.update(end);
		}

		end.clear();

		end.draw(background);
		end.draw(backgroundSecond);
		end.draw(text);

		for (auto& i : buttons) {
			i.drawTo(end);
		}

		settingFade(end, blackScreen, fadeOut, alpha, state);

		end.display();
	}
}

//ther (next three function) require moving to a separate file. 
void loadRecords() {
	std::ifstream file("record.txt");
	if (file.is_open()) {
		file >> firstRecord >> secondRecord >> thirdRecord >> fourthRecord >> dynamicRecord;
		file.close();
	}
	else {
		firstRecord = secondRecord = thirdRecord = fourthRecord = dynamicRecord = 0;
	}
}

void saveRecords() {
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

void startText(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField) {
	size_t rows = thirdField.size();
	size_t cols = thirdField[0].size();

	sf::Text textStart;
	textStart.setString("   Press any key\n to start the game");
	textStart.setFont(fontMain);
	textStart.setCharacterSize(36);
	textStart.setFillColor(sf::Color(255, 250, 205));
	textStart.setStyle(sf::Text::Bold);

	sf::FloatRect textRect = textStart.getGlobalBounds();

	textStart.setPosition(static_cast<float>(offsetX + (cols * cellSize - textRect.width) / 2),
						  static_cast<float>(offsetY + (rows * cellSize - textRect.height - 200) / 2));

	window.draw(textStart);
}

void startGameWithSettings(gameState& state) {
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Snake Game", sf::Style::Fullscreen);
	averageWindow(window);

	window.setMouseCursorVisible(false);

	sf::Sprite background;
	background.setTexture(backgroundSecond);

	sf::Vector2u windowSize = window.getSize();
	std::cout << windowSize.x << " " << windowSize.y;
	background.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));

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
	case '4':
		field = barier();
		break;
	default:
		field = barier();
		break;
	}

	mainSound();

	if (inputArcad != '3') {
		speedDirection();
	}
	startPosition(field, snake);
	food(field);

	/*while (!startKey && window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			window.clear();

			window.draw(background);
			draw(window, field, snake);
			startText(window, field);
			if (event.type == sf::Event::KeyPressed) {
				startKey = true;
				levelTimer.restart();
				window.close();
				break;
			}

			window.display();
		}
	}*/

	while (window.isOpen()) {
		sf::Event event;
		bool directionChanged = false;
		while (window.pollEvent(event)) {
			if (input == '5') {
				dynamicSpeed();
			}

			if (event.type == sf::Event::KeyPressed) {
				startKey = true;
				levelTimer.restart();
			}

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

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (!startKey) {
			window.clear();
			window.draw(background);
			draw(window, field, snake);
			startText(window, field);
			window.display();
		}
		else {

			if (state == GAME && startKey) {

				chooceArcad(window, state, field, snake);

				directionChanged = false;

				window.clear();

				window.draw(background);

				if (inputArcad == '4') {
					fieldChoose(window, field, snake);
					textureSnake(window, snake);
					isStyleChosen = false;
					scoreArcad(window, field);
				}
				else {
					draw(window, field, snake);
					textureSnake(window, snake);
					if (inputArcad == '3') {
						timeArcad(window, field);
						scoreArcad(window, field);
					}
					else {
						coundScore(window, field);
					}
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
	}
	music.stop();
}

void recordMenu(gameState& state) {
	sf::RenderWindow record(sf::VideoMode(1920, 1080), "Record", sf::Style::Fullscreen);

	Cursor::setCostumCursor(record, "backgroundTexture/hand.png");

	sf::Sprite background;
	background.setTexture(backgroundSecond);

	sf::Vector2u recordSize = record.getSize();
	background.setTextureRect(sf::IntRect(0, 0, recordSize.x, recordSize.y));

	sf::Sprite backgroundSecond;
	backgroundSecond.setTexture(textureBackSecond);

	float styleWidth = static_cast<float>(rows) * static_cast<float>(cellSize);
	float styleHeight = static_cast<float>(cols) * static_cast<float>(cellSize);

	float offX = (recordSize.x - styleWidth) / 2.0f;
	float offY = (recordSize.y - styleHeight) / 2.0f;

	backgroundSecond.setPosition({ offX - 90, offY - 25 });

	Button menu = createSecondButton("menu", buttonBackNormal, { recordSize.x / 2.0f, 840 }, { 150, 45 });

	std::vector<sf::Text> Text = {
		createText(" Quickly\nScore: " + std::to_string(firstRecord), { 620, 150 }),
		createText("  Fast\nScore: " + std::to_string(secondRecord), { 1060, 150 }),
		createText(" Medium\nScore: " + std::to_string(thirdRecord), { 620, 390 }),
		createText("  Slow\nScore: " + std::to_string(fourthRecord), { 1060, 390 }),
		createText("Dynamic\nScore: " + std::to_string(dynamicRecord), { 840, 590 })
	};

	sf::RectangleShape blackScreen;
	int alpha;
	bool fadeOut = false;

	createParametrs(blackScreen, alpha);

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

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (menu.getPressed()) {
						menu.setPressed(false);
						menu.textureUpdate(record, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						fadeOut = true;
						state = MENU;
					}
				}
			}

			menu.update(record);
		}

		record.clear();

		record.draw(background);
		record.draw(backgroundSecond);
		for (auto& i : Text) {
			record.draw(i);
		}
		menu.drawTo(record);

		settingFade(record, blackScreen, fadeOut, alpha, state);

		record.display();
	}
}

void arcad(gameState& state, int page = 1) {
	while (true) {
		sf::RenderWindow ArcadWindow(sf::VideoMode(1920, 1080), "Arcad", sf::Style::Fullscreen);

		Cursor::setCostumCursor(ArcadWindow, "backgroundTexture/hand.png");

		sf::Texture styleFirst, styleSecond, styleThird, styleFourth;
		if (page == 1) {
			styleFirst.loadFromFile("style/arcad1.png");
			styleSecond.loadFromFile("style/arcad2.png");
			styleThird.loadFromFile("style/arcad3.png");
			styleFourth.loadFromFile("style/arcad4.png");
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

		displayArcadWindow(ArcadWindow, state, styleFirst, styleSecond, styleThird, styleFourth, page);

		if (state != ARCAD) {
			break;
		}
	}
}

void menuBar(gameState& state) {
	sf::RenderWindow menu(sf::VideoMode(1920, 1080), "Menu", sf::Style::Fullscreen);

	Cursor::setCostumCursor(menu, "backgroundTexture/hand.png");

	sf::Sprite background;
	background.setTexture(textureBack);

	sf::Text title("Snake Game", fontPixel, 200);
	title.setFillColor(sf::Color::White);
	title.setStyle(sf::Text::Bold);
	title.setOutlineThickness(3.0f);
	sf::FloatRect titleBounds = title.getGlobalBounds();
	title.setOrigin(titleBounds.width / 2.0f, titleBounds.height / 2.0f);
	title.setPosition(960, 70);

	std::vector<Button> buttons = {
		createButton("start",buttonBackNormal, { 960, 310 }, { 250, 60 }),
		createButton("style", buttonBackNormal, { 960, 470 }, { 250, 65 }),
		createButton("arcade", buttonBackNormal, { 960, 630 }, { 250, 55 }),
		createButton("record", buttonBackNormal, { 960, 790 }, { 250, 55 }),
		createButton("exit", buttonBackNormal, { 960, 950 }, { 250, 60 })
	};

	Button soundTest("sound", { 150, 130 }, 80, sf::Color::White);
	soundTest.setTexture(checkSound ? buttonNullSoundNormal : buttonFullSoundNormal);
	soundTest.setPosition({ 1810, 990 });

	sf::RectangleShape blackScreen;
	int alpha;
	bool fadeOut = false;

	createParametrs(blackScreen, alpha);

	while (menu.isOpen()) {
		sf::Event event;
		while (menu.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (size_t i = 0; i < buttons.size(); ++i) {
						if (buttons[i].mousePosition(menu)) {
							buttons[i].setPressed(true);
							buttons[i].textureUpdate(menu, buttonBackClick, buttonBackNormal);
							soundBotton();
						}
					}

					if (soundTest.mousePosition(menu)) {
						soundTest.setPressed(true);
						soundTest.textureUpdate(menu, checkSound ? buttonNullSoundClick : buttonFullSoundClick, checkSound ? buttonNullSoundNormal : buttonFullSoundNormal);
						soundBotton();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					for (size_t i = 0; i < buttons.size(); ++i) {
						if (buttons[i].getPressed()) {
							buttons[i].setPressed(false);
							buttons[i].textureUpdate(menu, buttonBackClick, buttonBackNormal);
							sf::sleep(sf::milliseconds(120));

							if (i == 0) state = START;
							if (i == 1) state = STYLE;
							if (i == 2) state = ARCAD;
							if (i == 3) state = RECORD;
							if (i == 4) state = CLOSE;

							fadeOut = true;
						}
					}

					if (soundTest.getPressed()) {
						soundTest.setPressed(false);
						soundTest.textureUpdate(menu, checkSound ? buttonFullSoundClick : buttonNullSoundClick, checkSound ? buttonFullSoundNormal : buttonNullSoundNormal);
						sf::sleep(sf::milliseconds(120));
						soundTest.setTexture(checkSound ? buttonFullSoundNormal : buttonNullSoundNormal);
						if (!checkSound)
							checkSound = true;
						else
							checkSound = false;
					}
				}
			}
		}

		for (auto& i : buttons) {
			i.update(menu);
		}
		soundTest.update(menu);

		menu.clear();
		menu.draw(background);
		menu.draw(title);

		for (auto& i : buttons) {
			i.drawTo(menu);
		}
		soundTest.drawTo(menu);

		settingFade(menu, blackScreen, fadeOut, alpha, state);

		menu.display();
	}
}

void handleState(sf::RenderWindow& window, gameState& state) {
	switch (state)
	{
	case MENU:
		menuBar(state);
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
		recordMenu(state);
		break;
	case GAME:
		startGameWithSettings(state);
		break;
	case END:
		endGame(state);

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
			if (inputArcad == '4') {
				next = 2;
				count = 1;
				inputStyle = '1';
				flagStyle = false;
				win = false;
			}
			startKey = false;
		}
		else {
			if (inputArcad == '4') {
				next = 2;
				count = 1;
				inputStyle = '1';
				flagStyle = false;
			}

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
	case CLOSE:
		window.close();
		break;
	}
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));

	loadFont();
	loadTextures();

	loadRecords();

	sf::RenderWindow windowMain(sf::VideoMode(1920, 1080), "handleMenu", sf::Style::Fullscreen);

	windowMain.clear(sf::Color::Black);
	windowMain.display();

	while (windowMain.isOpen()) {
		windowMain.clear(sf::Color::Black);

		handleState(windowMain, state);

		windowMain.display();
	}

	saveRecords();

	return 0;
}