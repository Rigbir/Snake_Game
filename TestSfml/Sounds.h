#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

extern sf::Music music;
extern sf::Music endMusic;
extern sf::SoundBuffer buffer;

void foodSound(bool checkSound);

void endSound(bool checkSound);

void mainSound(bool checkSound);

void soundBotton(bool checkSound);