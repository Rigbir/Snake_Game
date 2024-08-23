#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

sf::Texture bodyVertical, bodyHorizontal, leftUp, rightUp, leftDown, rightDown;
sf::Texture headUp, headDown, headLeft, headRight;
sf::Texture tailUp, tailLeft, tailRight, tailDown;

void firstTexture() {

	if (!bodyVertical.loadFromFile("firstSnakeTexture/bodyVert.png") ||
		!bodyHorizontal.loadFromFile("firstSnakeTexture/bodyHor.png") ||
		!leftUp.loadFromFile("firstSnakeTexture/leftUp.png") ||
		!rightUp.loadFromFile("firstSnakeTexture/rightUp.png") ||
		!leftDown.loadFromFile("firstSnakeTexture/leftDown.png") ||
		!rightDown.loadFromFile("firstSnakeTexture/rightDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!headUp.loadFromFile("firstSnakeTexture/headUp.png") ||
		!headDown.loadFromFile("firstSnakeTexture/headDown.png") ||
		!headLeft.loadFromFile("firstSnakeTexture/headLeft.png") ||
		!headRight.loadFromFile("firstSnakeTexture/headRight.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!tailUp.loadFromFile("firstSnakeTexture/tailUp.png") ||
		!tailLeft.loadFromFile("firstSnakeTexture/tailLeft.png") ||
		!tailRight.loadFromFile("firstSnakeTexture/tailRight.png") ||
		!tailDown.loadFromFile("firstSnakeTexture/tailDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}
}

void secondTexture() {

	if (!bodyVertical.loadFromFile("secondSnakeTexture/bodyVert.png") ||
		!bodyHorizontal.loadFromFile("secondSnakeTexture/bodyHor.png") ||
		!leftUp.loadFromFile("secondSnakeTexture/leftUp.png") ||
		!rightUp.loadFromFile("secondSnakeTexture/rightUp.png") ||
		!leftDown.loadFromFile("secondSnakeTexture/leftDown.png") ||
		!rightDown.loadFromFile("secondSnakeTexture/rightDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!headUp.loadFromFile("secondSnakeTexture/headUp.png") ||
		!headDown.loadFromFile("secondSnakeTexture/headDown.png") ||
		!headLeft.loadFromFile("secondSnakeTexture/headLeft.png") ||
		!headRight.loadFromFile("secondSnakeTexture/headRight.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!tailUp.loadFromFile("secondSnakeTexture/tailUp.png") ||
		!tailLeft.loadFromFile("secondSnakeTexture/tailLeft.png") ||
		!tailRight.loadFromFile("secondSnakeTexture/tailRight.png") ||
		!tailDown.loadFromFile("secondSnakeTexture/tailDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}
}

void thirdTexture() {

	if (!bodyVertical.loadFromFile("thirdSnakeTexture/bodyVert.png") ||
		!bodyHorizontal.loadFromFile("thirdSnakeTexture/bodyHor.png") ||
		!leftUp.loadFromFile("thirdSnakeTexture/leftUp.png") ||
		!rightUp.loadFromFile("thirdSnakeTexture/rightUp.png") ||
		!leftDown.loadFromFile("thirdSnakeTexture/leftDown.png") ||
		!rightDown.loadFromFile("thirdSnakeTexture/rightDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!headUp.loadFromFile("thirdSnakeTexture/headUp.png") ||
		!headDown.loadFromFile("thirdSnakeTexture/headDown.png") ||
		!headLeft.loadFromFile("thirdSnakeTexture/headLeft.png") ||
		!headRight.loadFromFile("thirdSnakeTexture/headRight.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!tailUp.loadFromFile("thirdSnakeTexture/tailUp.png") ||
		!tailLeft.loadFromFile("thirdSnakeTexture/tailLeft.png") ||
		!tailRight.loadFromFile("thirdSnakeTexture/tailRight.png") ||
		!tailDown.loadFromFile("thirdSnakeTexture/tailDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}
}

void fourthTexture() {

	if (!bodyVertical.loadFromFile("fourthSnakeTexture/bodyVert.png") ||
		!bodyHorizontal.loadFromFile("fourthSnakeTexture/bodyHor.png") ||
		!leftUp.loadFromFile("fourthSnakeTexture/leftUp.png") ||
		!rightUp.loadFromFile("fourthSnakeTexture/rightUp.png") ||
		!leftDown.loadFromFile("fourthSnakeTexture/leftDown.png") ||
		!rightDown.loadFromFile("fourthSnakeTexture/rightDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!headUp.loadFromFile("fourthSnakeTexture/headUp.png") ||
		!headDown.loadFromFile("fourthSnakeTexture/headDown.png") ||
		!headLeft.loadFromFile("fourthSnakeTexture/headLeft.png") ||
		!headRight.loadFromFile("fourthSnakeTexture/headRight.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}

	if (!tailUp.loadFromFile("fourthSnakeTexture/tailUp.png") ||
		!tailLeft.loadFromFile("fourthSnakeTexture/tailLeft.png") ||
		!tailRight.loadFromFile("fourthSnakeTexture/tailRight.png") ||
		!tailDown.loadFromFile("fourthSnakeTexture/tailDown.png")
		) {
		std::cerr << RED_TEXT << "Error loading texture file" << RESET_TEXT << std::endl;
		return;
	}
}

void styleChooce(char& inputStyle) {
	switch (inputStyle)
	{
	case '1':
		firstTexture();
		break;
	case '2':
		secondTexture();
		break;
	case '3':
		thirdTexture();
		break;
	case '4':
		fourthTexture();
		break;
	}
}