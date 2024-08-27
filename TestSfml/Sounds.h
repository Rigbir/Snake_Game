#pragma once

#include <iostream>
#include <SFML/Audio.hpp>

#define RED_TEXT "\033[1;31m"
#define RESET_TEXT "\033[0m"

sf::Music music;
sf::Music endMusic;
sf::SoundBuffer buffer;

void foodSound() {
	if (!buffer.loadFromFile("Music/SoundMoney.wav")) {
		std::cerr << RED_TEXT << "Error loading sound file" << RESET_TEXT << std::endl;
		return;
	}
	static sf::Sound eatSound;
	eatSound.setBuffer(buffer);
	eatSound.setVolume(100);
	eatSound.play();
}

void endSound() {
	if (!endMusic.openFromFile("Music/gameOver.wav")) {
		std::cerr << RED_TEXT << "Error loading sound file" << RESET_TEXT << std::endl;
		return;
	}
	endMusic.setVolume(100);
	endMusic.play();
}

void mainSound() {
	if (!music.openFromFile("Music/electro.wav")) {
		std::cerr << RED_TEXT << "Error loading sound file" << RESET_TEXT << std::endl;
		return;
	}
	music.setLoop(true);
	music.play();
}

void soundBotton() {
	if (!buffer.loadFromFile("Music/menuChoice.wav")) {
		std::cerr << RED_TEXT << "Error loading sound file" << RESET_TEXT << std::endl;
		return;
	}
	static sf::Sound bottonSound;
	bottonSound.setBuffer(buffer);
	bottonSound.setVolume(100);
	bottonSound.play();
}