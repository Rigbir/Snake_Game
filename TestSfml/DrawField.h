#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "globals.h"

void drawBlackField(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {

	sf::Texture food;
	if (!food.loadFromFile("firstSnakeTexture/food.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteFood;
	spriteFood.setTexture(food);

	float scaleX = static_cast<float>(35) / food.getSize().x;
	float scaleY = static_cast<float>(35) / food.getSize().y;
	spriteFood.setScale(scaleX, scaleY);

	sf::Texture barierTime;
	if (!barierTime.loadFromFile("firstSnakeTexture/poison.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarierTime;
	spriteBarierTime.setTexture(barierTime);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 25; ++j) {
			sf::RectangleShape rectangle(sf::Vector2f(35, 35));
			rectangle.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));

			if (field[i][j] == '1') {
				rectangle.setFillColor(sf::Color(80, 80, 80));
			}
			else if (field[i][j] == '@') {
				spriteFood.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteFood);
				continue;
			}
			else if (field[i][j] == '2') {
				spriteBarierTime.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarierTime);
				continue;
			}
			else {
				rectangle.setFillColor(sf::Color::Black);
			}
			window.draw(rectangle);
		}

	}
}

void drawGreenField(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {

	sf::Texture food[8];
	if (!food[0].loadFromFile("fifthSnakeTexture/food.png") ||
		!food[1].loadFromFile("fifthSnakeTexture/food1.png") ||
		!food[2].loadFromFile("fifthSnakeTexture/food2.png") ||
		!food[3].loadFromFile("fifthSnakeTexture/food3.png") ||
		!food[4].loadFromFile("fifthSnakeTexture/food4.png") ||
		!food[5].loadFromFile("fifthSnakeTexture/food5.png") ||
		!food[6].loadFromFile("fifthSnakeTexture/food6.png") ||
		!food[7].loadFromFile("fifthSnakeTexture/food7.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Texture fieldTexture;
	if (!fieldTexture.loadFromFile("fifthSnakeTexture/field.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteField;
	spriteField.setTexture(fieldTexture);

	sf::Texture barier;
	if (!barier.loadFromFile("fifthSnakeTexture/barier.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarier;
	spriteBarier.setTexture(barier);

	sf::Texture barierTime;
	if (!barierTime.loadFromFile("fifthSnakeTexture/grave.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarierTime;
	spriteBarierTime.setTexture(barierTime);

	sf::Texture textures[8];
	if (!textures[0].loadFromFile("fifthSnakeTexture/fieldBorderDown.png") ||
		!textures[1].loadFromFile("fifthSnakeTexture/fieldBorderLeft.png") ||
		!textures[2].loadFromFile("fifthSnakeTexture/fieldBorderRight.png") ||
		!textures[3].loadFromFile("fifthSnakeTexture/fieldBorderTop.png") ||
		!textures[4].loadFromFile("fifthSnakeTexture/fieldLeftDown.png") ||
		!textures[5].loadFromFile("fifthSnakeTexture/fieldLeftUp.png") ||
		!textures[6].loadFromFile("fifthSnakeTexture/fieldRightDown.png") ||
		!textures[7].loadFromFile("fifthSnakeTexture/fieldRightUp.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 25; ++j) {
			sf::Sprite spriteBorder;
			sf::Sprite spriteFood;

			if (i == 0 && j == 0) {
				spriteBorder.setTexture(textures[7]);
			}
			else if (i == 0 && j == 24) {
				spriteBorder.setTexture(textures[5]);
			}
			else if (i == 19 && j == 0) {
				spriteBorder.setTexture(textures[6]);
			}
			else if (i == 19 && j == 24) {
				spriteBorder.setTexture(textures[4]);
			}
			else if (i == 0) {
				spriteBorder.setTexture(textures[3]);
			}
			else if (i == 19) {
				spriteBorder.setTexture(textures[0]);
			}
			else if (j == 0) {
				spriteBorder.setTexture(textures[1]);
			}
			else if (j == 24) {
				spriteBorder.setTexture(textures[2]);
			}
			else if (field[i][j] == '@') {
				if (foodIndex < 8) {
					spriteFood.setTexture(food[foodIndex]);

					float scaleX = static_cast<float>(35) / food[foodIndex].getSize().x;
					float scaleY = static_cast<float>(35) / food[foodIndex].getSize().y;
					spriteFood.setScale(scaleX, scaleY);

					spriteFood.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
					window.draw(spriteFood);
					continue;
				}
				else if (foodIndex == 8) {
					foodIndex = 0;
					spriteFood.setTexture(food[foodIndex]);

					float scaleX = static_cast<float>(35) / food[foodIndex].getSize().x;
					float scaleY = static_cast<float>(35) / food[foodIndex].getSize().y;
					spriteFood.setScale(scaleX, scaleY);

					spriteFood.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
					window.draw(spriteFood);
					continue;
				}
			}
			else if (field[i][j] == '1') {
				spriteBarier.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarier);
				continue;
			}
			else if (field[i][j] == '2') {
				spriteBarierTime.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarierTime);
				continue;
			}
			else {
				spriteField.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteField);
				continue;
			}

			spriteBorder.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
			window.draw(spriteBorder);
		}
	}
}

void drawGreyField(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {

	sf::Texture food;
	if (!food.loadFromFile("sixSnakeTexture/food.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteFood;
	spriteFood.setTexture(food);

	float scaleX = static_cast<float>(35) / food.getSize().x;
	float scaleY = static_cast<float>(35) / food.getSize().y;
	spriteFood.setScale(scaleX, scaleY);

	sf::Texture fieldTexture;
	if (!fieldTexture.loadFromFile("sixSnakeTexture/field.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteField;
	spriteField.setTexture(fieldTexture);

	sf::Texture textures[8];
	if (!textures[0].loadFromFile("sixSnakeTexture/fieldBorderDown.png") ||
		!textures[1].loadFromFile("sixSnakeTexture/fieldBorderLeft.png") ||
		!textures[2].loadFromFile("sixSnakeTexture/fieldBorderRight.png") ||
		!textures[3].loadFromFile("sixSnakeTexture/fieldBorderTop.png") ||
		!textures[4].loadFromFile("sixSnakeTexture/fieldLeftDown.png") ||
		!textures[5].loadFromFile("sixSnakeTexture/fieldLeftUp.png") ||
		!textures[6].loadFromFile("sixSnakeTexture/fieldRightDown.png") ||
		!textures[7].loadFromFile("sixSnakeTexture/fieldRightUp.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Texture barier;
	if (!barier.loadFromFile("sixSnakeTexture/barier.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarier;
	spriteBarier.setTexture(barier);

	sf::Texture barierTime;
	if (!barierTime.loadFromFile("sixSnakeTexture/asteroid2.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarierTime;
	spriteBarierTime.setTexture(barierTime);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 25; ++j) {
			sf::Sprite spriteBorder;

			if (i == 0 && j == 0) {
				spriteBorder.setTexture(textures[7]); 
			}
			else if (i == 0 && j == 24) {
				spriteBorder.setTexture(textures[5]); 
			}
			else if (i == 19 && j == 0) {
				spriteBorder.setTexture(textures[6]); 
			}
			else if (i == 19 && j == 24) {
				spriteBorder.setTexture(textures[4]); 
			}
			else if (i == 0) {
				spriteBorder.setTexture(textures[3]); 
			}
			else if (i == 19) {
				spriteBorder.setTexture(textures[0]); 
			}
			else if (j == 0) {
				spriteBorder.setTexture(textures[1]); 
			}
			else if (j == 24) {
				spriteBorder.setTexture(textures[2]); 
			}

			else if (field[i][j] == '@') {
				spriteFood.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteFood);
				continue;
			}
			else if (field[i][j] == '1') {
				spriteBarier.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarier);
				continue;
			}
			else if (field[i][j] == '2') {
				spriteBarierTime.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarierTime);
				continue;
			}
			else {
				spriteField.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteField);
				continue;
			}

			spriteBorder.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
			window.draw(spriteBorder);
		}
	}
}

void drawSpaceField(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {

	sf::Texture food[13];
	if (!food[0].loadFromFile("sevenSnakeTexture/food.png") ||
		!food[1].loadFromFile("sevenSnakeTexture/food1.png") ||
		!food[2].loadFromFile("sevenSnakeTexture/food2.png") ||
		!food[3].loadFromFile("sevenSnakeTexture/food3.png") ||
		!food[4].loadFromFile("sevenSnakeTexture/food4.png") ||
		!food[5].loadFromFile("sevenSnakeTexture/food5.png") ||
		!food[6].loadFromFile("sevenSnakeTexture/food6.png") ||
		!food[7].loadFromFile("sevenSnakeTexture/food7.png") ||
		!food[8].loadFromFile("sevenSnakeTexture/food8.png") ||
		!food[9].loadFromFile("sevenSnakeTexture/food9.png") ||
		!food[10].loadFromFile("sevenSnakeTexture/food10.png") ||
		!food[11].loadFromFile("sevenSnakeTexture/food11.png") ||
		!food[12].loadFromFile("sevenSnakeTexture/food12.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Texture fieldTexture;
	if (!fieldTexture.loadFromFile("sevenSnakeTexture/field.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteField;
	spriteField.setTexture(fieldTexture);

	sf::Texture textures[8];
	if (!textures[0].loadFromFile("sevenSnakeTexture/fieldBorderDown.png") ||
		!textures[1].loadFromFile("sevenSnakeTexture/fieldBorderLeft.png") ||
		!textures[2].loadFromFile("sevenSnakeTexture/fieldBorderRight.png") ||
		!textures[3].loadFromFile("sevenSnakeTexture/fieldBorderTop.png") ||
		!textures[4].loadFromFile("sevenSnakeTexture/fieldLeftDown.png") ||
		!textures[5].loadFromFile("sevenSnakeTexture/fieldLeftUp.png") ||
		!textures[6].loadFromFile("sevenSnakeTexture/fieldRightDown.png") ||
		!textures[7].loadFromFile("sevenSnakeTexture/fieldRightUp.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Texture barier;
	if (!barier.loadFromFile("sevenSnakeTexture/barier.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarier;
	spriteBarier.setTexture(barier);

	sf::Texture barierTime;
	if (!barierTime.loadFromFile("sevenSnakeTexture/asteroid.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarierTime;
	spriteBarierTime.setTexture(barierTime);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 25; ++j) {
			sf::Sprite spriteBorder;
			sf::Sprite spriteFood;

			if (i == 0 && j == 0) {
				spriteBorder.setTexture(textures[7]);
			}
			else if (i == 0 && j == 24) {
				spriteBorder.setTexture(textures[5]);
			}
			else if (i == 19 && j == 0) {
				spriteBorder.setTexture(textures[6]);
			}
			else if (i == 19 && j == 24) {
				spriteBorder.setTexture(textures[4]);
			}
			else if (i == 0) {
				spriteBorder.setTexture(textures[3]);
			}
			else if (i == 19) {
				spriteBorder.setTexture(textures[0]);
			}
			else if (j == 0) {
				spriteBorder.setTexture(textures[1]);
			}
			else if (j == 24) {
				spriteBorder.setTexture(textures[2]);
			}

			else if (field[i][j] == '@') {
				if (foodIndex < 13) {
					spriteFood.setTexture(food[foodIndex]);

					float scaleX = static_cast<float>(35) / food[foodIndex].getSize().x;
					float scaleY = static_cast<float>(35) / food[foodIndex].getSize().y;
					spriteFood.setScale(scaleX, scaleY);

					spriteFood.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
					window.draw(spriteFood);
					continue;
				}
				else if (foodIndex == 13) {
					foodIndex = 0;
					spriteFood.setTexture(food[foodIndex]);

					float scaleX = static_cast<float>(35) / food[foodIndex].getSize().x;
					float scaleY = static_cast<float>(35) / food[foodIndex].getSize().y;
					spriteFood.setScale(scaleX, scaleY);

					spriteFood.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
					window.draw(spriteFood);
					continue;
				}
			}
			else if (field[i][j] == '1') {
				spriteBarier.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarier);
				continue;
			}
			else if (field[i][j] == '2') {
				spriteBarierTime.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarierTime);
				continue;
			}
			else {
				spriteField.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteField);
				continue;
			}

			spriteBorder.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
			window.draw(spriteBorder);
		}
	}
}

void drawCatField(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {

	sf::Texture food;
	if (!food.loadFromFile("eightSnakeTexture/food.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteFood;
	spriteFood.setTexture(food);

	float scaleX = static_cast<float>(35) / food.getSize().x;
	float scaleY = static_cast<float>(35) / food.getSize().y;
	spriteFood.setScale(scaleX, scaleY);

	sf::Texture fieldTexture;
	if (!fieldTexture.loadFromFile("eightSnakeTexture/field4.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteField;
	spriteField.setTexture(fieldTexture);

	sf::Texture textures[8];
	if (!textures[0].loadFromFile("eightSnakeTexture/fieldBorderDown.png") ||
		!textures[1].loadFromFile("eightSnakeTexture/fieldBorderLeft.png") ||
		!textures[2].loadFromFile("eightSnakeTexture/fieldBorderRight.png") ||
		!textures[3].loadFromFile("eightSnakeTexture/fieldBorderTop.png") ||
		!textures[4].loadFromFile("eightSnakeTexture/fieldLeftDown.png") ||
		!textures[5].loadFromFile("eightSnakeTexture/fieldLeftUp.png") ||
		!textures[6].loadFromFile("eightSnakeTexture/fieldRightDown.png") ||
		!textures[7].loadFromFile("eightSnakeTexture/fieldRightUp.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Texture barier;
	if (!barier.loadFromFile("eightSnakeTexture/barier.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarier;
	spriteBarier.setTexture(barier);

	sf::Texture barierTime;
	if (!barierTime.loadFromFile("eightSnakeTexture/sausage.png")) {
		std::cerr << "Error loading texture file" << std::endl;
		return;
	}

	sf::Sprite spriteBarierTime;
	spriteBarierTime.setTexture(barierTime);

	for (int i = 0; i < 20; ++i) {
		for (int j = 0; j < 25; ++j) {
			sf::Sprite spriteBorder;

			if (i == 0 && j == 0) {
				spriteBorder.setTexture(textures[7]);
			}
			else if (i == 0 && j == 24) {
				spriteBorder.setTexture(textures[5]);
			}
			else if (i == 19 && j == 0) {
				spriteBorder.setTexture(textures[6]);
			}
			else if (i == 19 && j == 24) {
				spriteBorder.setTexture(textures[4]);
			}
			else if (i == 0) {
				spriteBorder.setTexture(textures[3]);
			}
			else if (i == 19) {
				spriteBorder.setTexture(textures[0]);
			}
			else if (j == 0) {
				spriteBorder.setTexture(textures[1]);
			}
			else if (j == 24) {
				spriteBorder.setTexture(textures[2]);
			}

			else if (field[i][j] == '@') {
				spriteFood.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteFood);
				continue;
			}
			else if (field[i][j] == '1') {
				spriteBarier.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarier);
				continue;
			}
			else if (field[i][j] == '2') {
				spriteBarierTime.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteBarierTime);
				continue;
			}
			else {
				spriteField.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
				window.draw(spriteField);
				continue;
			}
			
			spriteBorder.setPosition(static_cast<float>(j * 35 + offsetX), static_cast<float>(i * 35 + offsetY - 120));
			window.draw(spriteBorder);
		}

	}
}

void fieldChoose(sf::RenderWindow& window, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake) {
	switch (inputStyle){
	case '1':
		drawBlackField(window, field, snake);
		break;
	case '2':
		drawBlackField(window, field, snake);
		break;
	case '3':
		drawBlackField(window, field, snake);
		break;
	case '4':
		drawBlackField(window, field, snake);
		break;
	case '5':
		drawGreenField(window, field, snake);
		break;
	case '6':
		drawGreyField(window, field, snake);
		break;
	case '7':
		drawSpaceField(window, field, snake);
		break;
	case '8':
		drawCatField(window, field, snake);
		break;
	default:
		drawBlackField(window, field, snake);
		break;
	}
}