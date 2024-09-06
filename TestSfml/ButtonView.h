#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "Font.h"

Button createButton(const std::string& text, sf::Texture& textureBack, const sf::Vector2f& position, const sf::Vector2f& origin);

Button createSecondButton(const std::string& text, sf::Texture& textureBack, const sf::Vector2f& position, const sf::Vector2f& origin);

sf::Text createText(const std::string& name, const sf::Vector2f& position);