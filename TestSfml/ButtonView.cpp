#include "ButtonView.h"

Button createButton(const std::string& text, sf::Texture& textureBack, const sf::Vector2f& position, const sf::Vector2f& origin) {
	Button button(text, { 500, 130 }, 80, sf::Color::White);
	button.setFont(fontPixel);
	button.setTexture(textureBack);
	button.setTextOutline(3.0f);
	button.setTextStyle();
	button.setPosition(position);
	button.setOrigin(origin);
	return button;
}

Button createSecondButton(const std::string& text, sf::Texture& textureBack, const sf::Vector2f& position, const sf::Vector2f& origin) {
	Button buttonSecond(text, { 300, 100 }, 65, sf::Color::White);
	buttonSecond.setFont(fontPixel);
	buttonSecond.setTexture(textureBack);
	buttonSecond.setTextOutline(2.0f);
	buttonSecond.setTextStyle();
	buttonSecond.setPosition(position);
	buttonSecond.setOrigin(origin);
	return buttonSecond;
}

sf::Text createText(const std::string& name, const sf::Vector2f& position) {
	sf::Text text;
	text.setFont(fontMain);
	text.setString(name);
	text.setCharacterSize(65);
	text.setFillColor(sf::Color::White);
	text.setOutlineThickness(3.0f);
	text.setStyle(sf::Text::Bold);
	text.setPosition(position);
	return text;
}