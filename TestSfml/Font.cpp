#include <iostream>
#include "Font.h"

sf::Font fontMain;
sf::Font fontPixel;

void loadFont() {
	if (!fontMain.loadFromFile("font/arial.ttf") ||
		!fontPixel.loadFromFile("font/ArcadeClassic.ttf")) {
		std::cerr << "Error loading font file" << std::endl;
		return;
	}
}