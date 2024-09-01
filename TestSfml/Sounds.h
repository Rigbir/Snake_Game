#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include "globals.h"

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

extern sf::Music music;
extern sf::Music endMusic;
extern sf::SoundBuffer buffer;

void foodSound();

void punchSound();

void endSound();

void mainSound();

void soundBotton();