#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"

void createParametrs(sf::RectangleShape& blackScreen, int& alpha);

void settingFade(sf::RenderWindow& window, sf::RectangleShape& blackScreen, bool& fadeOut, int& alpha, gameState& state, gameState newState);