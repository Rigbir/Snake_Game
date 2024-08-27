#pragma once

#include "Arcad_manger.h"

static sf::SoundBuffer buffer3;

void soundBottonThird() {
	if (!buffer3.loadFromFile("Music/menuChoice.wav")) {
		return;
	}
	static sf::Sound bottonSound3;
	bottonSound3.setBuffer(buffer3);
	bottonSound3.setVolume(100);
	bottonSound3.play();
}

void displayArcadWindow(sf::RenderWindow& window, char& inputArcad, gameState& state, sf::Texture& backgroundFirst, sf::Texture& backgroundSecond, sf::Texture& styleFirst, sf::Texture& styleSecond, sf::Texture& styleThird, sf::Texture& styleFourth, sf::Texture& buttonBackNormal, sf::Texture& buttonBackClick, int& page) {
	
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

	Button first("", { 432, 350 }, 65, sf::Color::White);
	first.setTexture(styleFirst);
	first.setPosition({ ((windowSize.x - styleFirst.getSize().x) / 2.0f) - 4, (windowSize.y - styleFirst.getSize().y) / 2.0f - 113 });

	Button second("", { 432, 350 }, 65, sf::Color::White);
	second.setTexture(styleSecond);
	second.setPosition({ ((windowSize.x - styleSecond.getSize().x) / 2.0f) + styleSecond.getSize().x - 3, ((windowSize.y - styleFirst.getSize().y) / 2.0f) - 113 });

	Button third("", { 432, 350 }, 65, sf::Color::White);
	third.setTexture(styleThird);
	third.setPosition({ ((windowSize.x - styleThird.getSize().x) / 2.0f) - 4, ((windowSize.y - styleThird.getSize().y) / 2.0f) + styleThird.getSize().y - 113 });

	Button fourth("", { 432, 350 }, 65, sf::Color::White);
	fourth.setTexture(styleFourth);
	fourth.setPosition({ ((windowSize.x - styleThird.getSize().x) / 2.0f) + styleFourth.getSize().x - 3, ((windowSize.y - styleThird.getSize().y) / 2.0f) + styleFourth.getSize().y - 113 });

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

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (first.mousePosition(window)) {
						first.setPressed(true);
						soundBottonThird();
					}

					if (second.mousePosition(window)) {
						second.setPressed(true);
						soundBottonThird();
					}

					if (third.mousePosition(window)) {
						third.setPressed(true);
						soundBottonThird();
					}

					if (fourth.mousePosition(window)) {
						fourth.setPressed(true);
						soundBottonThird();
					}

					if (nextButton.mousePosition(window)) {
						nextButton.setPressed(true);
						nextButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						soundBottonThird();
					}

					if (backButton.mousePosition(window)) {
						backButton.setPressed(true);
						backButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						soundBottonThird();
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (first.getPressed()) {
						first.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputArcad = '1';
						else if (page == 2)
							inputArcad = '5';
						std::cout << "Input value style: " << inputArcad << std::endl;
						window.close();
						state = STYLE;
					}
					else if (second.getPressed()) {
						second.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputArcad = '2';
						else if (page == 2)
							inputArcad = '6';
						std::cout << "Input value style: " << inputArcad << std::endl;
						window.close();
						state = STYLE;
					}
					else if (third.getPressed()) {
						third.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputArcad = '3';
						else if (page == 2)
							inputArcad = '7';
						std::cout << "Input value style: " << inputArcad << std::endl;
						window.close();
						state = STYLE;
					}
					else if (fourth.getPressed()) {
						fourth.setPressed(false);
						sf::sleep(sf::milliseconds(100));
						if (page == 1)
							inputArcad = '4';
						else if (page == 2)
							inputArcad = '8';
						std::cout << "Input value style: " << inputArcad << std::endl;
						window.close();
						state = STYLE;
					}
					else if (nextButton.getPressed()) {
						nextButton.setPressed(false);
						nextButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						page++;
						window.close();
					}
					else if (backButton.getPressed()) {
						backButton.setPressed(false);
						backButton.textureUpdate(window, buttonBackClick, buttonBackNormal);
						sf::sleep(sf::milliseconds(120));
						page--;
						window.close();
					}
				}
			}

			first.styleUpdate(window);
			second.styleUpdate(window);
			third.styleUpdate(window);
			fourth.styleUpdate(window);
			if (page == 1) {
				nextButton.update(window);
			}
			else {
				nextButton.update(window);
				backButton.update(window);
			}

			window.clear();

			window.draw(backgroundSpriteSecond);
			window.draw(backgroundSpriteFirst);

			first.drawTo(window);
			second.drawTo(window);
			third.drawTo(window);
			fourth.drawTo(window);
			if (page == 1) {
				nextButton.drawTo(window);
			}
			else {
				nextButton.drawTo(window);
				backButton.drawTo(window);
			}

			window.display();
		}
	}
}