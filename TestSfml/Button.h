#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Button {
public:
	Button() {  }

	Button(std::string t, sf::Vector2f size, int charSize, sf::Color textColor) {
		text.setString(t);
		text.setFillColor(textColor);
		text.setCharacterSize(charSize);

		button.setSize(size);
		button.setOrigin(size.x / 2, size.y / 2);
		updateTextPosition();
	}

	void setFont(sf::Font& font) {
		text.setFont(font);
		updateTextPosition();
	}

	void setTextColor(sf::Color color) {
		text.setFillColor(color);
	}

	void setTextStyle() {
		text.setStyle(sf::Text::Bold);
	}

	void setTextOutline(float size) {
		text.setOutlineThickness(size);
		updateTextPosition();
	}

	void setPosition(sf::Vector2f pos) {
		button.setPosition(pos);
		updateTextPosition();
	}

	void setOrigin(sf::Vector2f origin) {
		button.setOrigin(origin);
		updateTextPosition();
	}

	void setTexture(sf::Texture& texture) {
		button.setTexture(&texture);
	}

	void setText(std::string t) {
		text.setString(t);
		updateTextPosition();
	}

	void drawTo(sf::RenderWindow& window) {
		window.draw(button);
		window.draw(text);
	}

	void setPressed(bool pressed) {
		isPressed = pressed;
	}

	bool getPressed() const {
		return isPressed;
	}

	bool mousePosition(sf::RenderWindow& window) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::FloatRect btnBounds = button.getGlobalBounds();

		return btnBounds.contains(static_cast<sf::Vector2f>(mousePos));
	}

	void textureUpdate(sf::RenderWindow& window, sf::Texture& buttonBackClick, sf::Texture& buttonBackNormal) {
		if (isPressed) {
			button.setTexture(&buttonBackClick);
		}
		else {
			button.setTexture(&buttonBackNormal);
		}
	}

	void update(sf::RenderWindow& window) {
		if (mousePosition(window)) {
			button.setScale(1.1f, 1.1f);
			button.setFillColor(sf::Color(188, 175, 175));
			button.setRotation(2.0f);
			text.setRotation(5.0f); 
			text.setFillColor(sf::Color(233, 225, 225));
		}
		else {
			button.setScale(1.0f, 1.0f);
			button.setFillColor(sf::Color(255, 255, 255));
			button.setRotation(0.0f);
			text.setRotation(0.0f); 
			text.setFillColor(sf::Color(255, 255, 255));
		}
	}

	void styleUpdate(sf::RenderWindow& window) {
		if (mousePosition(window)) {
			button.setScale(1.06f, 1.06f);
		}
		else {
			button.setScale(1.0f, 1.0f);
		}
	}

private:
	sf::RectangleShape button;
	sf::Text text;
	bool isPressed = false;

	void updateTextPosition() {
		sf::FloatRect textBounds = text.getLocalBounds();

		text.setOrigin(textBounds.left + textBounds.width / 2.0f,
					   textBounds.top + textBounds.height / 2.0f);

		text.setPosition(button.getPosition());
	}
};