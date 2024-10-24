#include "Fade.h"

void createParametrs(sf::RectangleShape& blackScreen, int& alpha) {
	blackScreen.setSize(sf::Vector2f(1920, 1080));
	blackScreen.setFillColor(sf::Color(0, 0, 0, 0));

	alpha = 0;
}

void settingFade(sf::RenderWindow& window, sf::RectangleShape& blackScreen, bool& fadeOut, int& alpha, gameState& state) {
	if (fadeOut) {
		if (alpha < 255) {
			alpha += 5;
			blackScreen.setFillColor(sf::Color(0, 0, 0, alpha));
		}
		else {
			window.clear();
			window.draw(blackScreen);
			window.display();
			window.close();
			fadeOut = false;
			state = state;
		}
		window.draw(blackScreen);
	}
}