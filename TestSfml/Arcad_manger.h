#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "gameState.h"
#include "Texture.h"
#include "globals.h"

void soundBottonThird();

void displayArcadWindow(sf::RenderWindow& window, gameState& state, sf::Texture& styleFirst, sf::Texture& styleSecond, sf::Texture& styleThird, sf::Texture& styleFourth, int& page);