#pragma once
#include <vector>
#include <iostream>
#include "Sounds.h"
#include "gameState.h"

#include "globals.h"

extern bool flagStyle;
extern int count;
extern int next;

void fourthArcadLogic(sf::RenderWindow& window, gameState& state, std::vector<std::vector<char>>& thirdField, std::vector<std::pair<int, int>>& snake);