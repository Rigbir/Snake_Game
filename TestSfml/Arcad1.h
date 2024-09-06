#pragma once
#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "gameState.h"

#include "globals.h"

std::vector<std::vector<char>> firstField();

void food(std::vector<std::vector<char>>& field);

bool foodCheck(std::vector<std::vector<char>>& field);

void firstArcadLogic(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake);

void chooceArcad(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& field, std::vector<std::pair<int, int>>& snake);