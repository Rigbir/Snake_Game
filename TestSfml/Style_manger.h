#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "gameState.h"

void soundBottonSecond();

void displayStyleWindow(sf::RenderWindow& window, char& inputStyle, gameState& state, sf::Texture& backgroundFirst, sf::Texture& backgroundSecond, sf::Texture& styleFirst, sf::Texture& styleSecond, sf::Texture& styleThird, sf::Texture& styleFourth, sf::Texture& buttonBackNormal, sf::Texture& buttonBackClick, int& page);