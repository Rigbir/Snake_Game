#pragma once

#include <vector>
#include <iostream>
#include "gameState.h"

#include "globals.h"

std::vector<std::vector<char>> thirdField();

void thirdArcadLogic(sf::RenderWindow& window, int& headX, int& headY, int& snakeLength, gameState& state, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake);

void timeArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField, int& offsetX, int& offsetY);

void scoreArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField, int& offsetX, int& offsetY);