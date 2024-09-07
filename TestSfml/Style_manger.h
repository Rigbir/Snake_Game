#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Button.h"
#include "Texture.h"
#include "gameState.h"
#include "globals.h"
#include "Fade.h"

void soundBottonSecond();

void displayStyleWindow(sf::RenderWindow& window, gameState& state, sf::Texture& styleFirst, sf::Texture& styleSecond, sf::Texture& styleThird, sf::Texture& styleFourth, int& page);