#pragma once

#include "Style_manger.h"

static sf::SoundBuffer buffer2;

void soundBottonSecond() {
	if (checkSound) return;

	if (!buffer2.loadFromFile("Music/menuChoice.wav")) {
		return;
	}
	static sf::Sound bottonSound2;
	bottonSound2.setBuffer(buffer2);
	bottonSound2.setVolume(100);
	bottonSound2.play();
}

void displayStyleWindow(sf::RenderWindow& window, gameState& state, sf::Texture& styleFirst, sf::Texture& styleSecond, sf::Texture& styleThird, sf::Texture& styleFourth, int& page) {

	sf::Font font;
	if (!font.loadFromFile("font/ArcadeClassic.ttf")) {
		return;
	}

	sf::Sprite backgroundSpriteSecond;
	backgroundSpriteSecond.setTexture(backgroundSecond);

	sf::Vector2u windowSize = window.getSize();
	backgroundSpriteSecond.setTextureRect(sf::IntRect(0, 0, windowSize.x, windowSize.y));
	window.draw(backgroundSpriteSecond);

	sf::Sprite backgroundSpriteFirst;
	backgroundSpriteFirst.setTexture(backgroundFirst);

	float styleWidth = 20 * 35;
	float styleHeight = 25 * 35;

	float offX = (windowSize.x - styleWidth) / 2.0f;
	float offY = (windowSize.y - styleHeight) / 2.0f;

	backgroundSpriteFirst.setPosition({ offX - 90, offY - 25 });
	window.draw(backgroundSpriteFirst);

	Button firstButton("", { 432, 350 }, 65, sf::Color::White);
	firstButton.setTexture(styleFirst);
	firstButton.setPosition({ ((windowSize.x - styleFirst.getSize().x) / 2.0f) - 4, (windowSize.y - styleFirst.getSize().y) / 2.0f - 113 });

	Button secondButton("", { 432, 350 }, 65, sf::Color::White);
	secondButton.setTexture(styleSecond);
	secondButton.setPosition({ ((windowSize.x - styleSecond.getSize().x) / 2.0f) + styleSecond.getSize().x - 3, ((windowSize.y - styleFirst.getSize().y) / 2.0f) - 113 });

	Button thirdButton("", { 432, 350 }, 65, sf::Color::White);
	thirdButton.setTexture(styleThird);
	thirdButton.setPosition({ ((windowSize.x - styleThird.getSize().x) / 2.0f) - 4, ((windowSize.y - styleThird.getSize().y) / 2.0f) + styleThird.getSize().y - 113 });

	Button fourthButton("", { 432, 350 }, 65, sf::Color::White);
	fourthButton.setTexture(styleFourth);
	fourthButton.setPosition({ ((windowSize.x - styleThird.getSize().x) / 2.0f) + styleFourth.getSize().x - 3, ((windowSize.y - styleThird.getSize().y) / 2.0f) + styleFourth.getSize().y - 113 });

	Button nextButton("Next", { 300, 100 }, 65, sf::Color::White);
	nextButton.setFont(font);
	nextButton.setTexture(buttonBackNormal);
	nextButton.setTextOutline(2.0f);
	nextButton.setTextStyle();
	nextButton.setPosition({ 1160, 890 });
	nextButton.setOrigin({ 150, 45 });

	Button backButton("Back", { 300, 100 }, 65, sf::Color::White);
	backButton.setFont(font);
	backButton.setTexture(buttonBackNormal);
	backButton.setTextOutline(2.0f);
	backButton.setTextStyle();
	backButton.setPosition({ 770, 890 });
	backButton.setOrigin({ 150, 45 });

	Button menuButton("menu", { 300, 100 }, 65, sf::Color::White);
	menuButton.setFont(font);
	menuButton.setTextStyle();
	menuButton.setTextOutline(2.0f);
	menuButton.setTexture(buttonBackNormal);
	menuButton.setPosition({ windowSize.x / 2.0f, 1005 });
	menuButton.setOrigin({ 150, 45 });

	sf::RectangleShape blackScreen;
	int alpha;
	bool fadeOut = false;

	createParametrs(blackScreen, alpha);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (firstButton.mousePosition(window)) {
						firstButton.setPressed(true);
						soundBottonSecond();
					}

					if (secondButton.mousePosition(window)) {
						secondButton.setPressed(true);
						soundBottonSecond();
					}

					if (thirdButton.mousePosition(window)) {
						thirdButton.setPressed(true);
						soundBottonSecond();
					}

					if (fourthButton.mousePosition(window)) {
						fourthButton.setPressed(true);
						soundBottonSecond();
					}

					if (nextButton.mousePosition(window)) {
						nextButton.setPressed(true);
						nextButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						soundBottonSecond();
					}

					if (backButton.mousePosition(window)) {
						backButton.setPressed(true);
						backButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						soundBottonSecond();
					}

					if (menuButton.mousePosition(window)) {
						menuButton.setPressed(true);
						menuButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						soundBottonSecond();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (firstButton.getPressed()) {
						firstButton.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputStyle = '1';
						else if (page == 2)
							inputStyle = '5';
						std::cout << "Input value style: " << inputStyle << std::endl;
						checkButton = true;
						if (inputArcad == '3') {
							sp = third;
							levelTimer.restart();
							fadeOut = true;
							state = GAME;
						}
						else {
							fadeOut = true;
							state = START;
						}
					}
					else if (secondButton.getPressed()) {
						secondButton.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputStyle = '2';
						else if (page == 2)
							inputStyle = '6';
						std::cout << "Input value style: " << inputStyle << std::endl;
						checkButton = true;
						if (inputArcad == '3') {
							sp = third;
							levelTimer.restart();
							fadeOut = true;
							state = GAME;
						}
						else {
							fadeOut = true;
							state = START;
						}
					}
					else if (thirdButton.getPressed()) {
						thirdButton.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputStyle = '3';
						else if (page == 2)
							inputStyle = '7';
						std::cout << "Input value style: " << inputStyle << std::endl;
						checkButton = true;
						if (inputArcad == '3') {
							sp = third;
							levelTimer.restart();
							fadeOut = true;
							state = GAME;
						}
						else {
							fadeOut = true;
							state = START;
						}
					}
					else if (fourthButton.getPressed()) {
						fourthButton.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputStyle = '4';
						else if (page == 2)
							inputStyle = '8';
						std::cout << "Input value style: " << inputStyle << std::endl;
						checkButton = true;
						if (inputArcad == '3') {
							sp = third;
							levelTimer.restart();
							fadeOut = true;
							state = GAME;
						}
						else {
							fadeOut = true;
							state = START;
						}
					}
					else if (nextButton.getPressed()) {
						nextButton.setPressed(false);
						nextButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						page++;
						fadeOut = true;
					}
					else if (backButton.getPressed()) {
						backButton.setPressed(false);
						backButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						page--;
						fadeOut = true;
					}
					else if (menuButton.getPressed()) {
						menuButton.setPressed(false);
						menuButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						checkButton = false;
						fadeOut = true;
						state = MENU;
					}
				}
			}
		}

		firstButton.styleUpdate(window);
		secondButton.styleUpdate(window);
		thirdButton.styleUpdate(window);
		fourthButton.styleUpdate(window);

		if (page == 1) {
			nextButton.update(window);
		}
		else {
			nextButton.update(window);
			backButton.update(window);
		}
		menuButton.update(window);

		window.clear();

		window.draw(backgroundSpriteSecond);
		window.draw(backgroundSpriteFirst);

		firstButton.drawTo(window);
		secondButton.drawTo(window);
		thirdButton.drawTo(window);
		fourthButton.drawTo(window);

		if (page == 1) {
			nextButton.drawTo(window);
		}
		else {
			nextButton.drawTo(window);
			backButton.drawTo(window);
		}
		menuButton.drawTo(window);

		settingFade(window, blackScreen, fadeOut, alpha, state);

		window.display();
	}
}
