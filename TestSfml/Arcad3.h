#pragma once

#include <vector>
#include <iostream>
#include "gameState.h"

#include "globals.h"

std::vector<std::vector<char>> thirdField();

void thirdArcadLogic(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake);

void timeArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField);

void scoreArcad(sf::RenderWindow& window, std::vector<std::vector<char>>& thirdField);