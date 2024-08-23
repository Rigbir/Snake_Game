#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Cursor {
public:
	static void setCostumCursor(sf::RenderWindow& window, const std::string& cursorPath) {

		sf::Texture cursorTexture;
		if (!cursorTexture.loadFromFile(cursorPath)) {
			std::cerr << "Error loading cursor texture from file: " << cursorPath << std::endl;
			return;
		}

		sf::Image cursorImage = cursorTexture.copyToImage();

		sf::Cursor cursor;
		if (!cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0))) {
			std::cerr << "Error creating custom cursor" << std::endl;
			return;
		}

		window.setMouseCursor(cursor);
	}
};

