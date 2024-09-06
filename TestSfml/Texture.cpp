#include <iostream>
#include "Texture.h"

sf::Texture buttonBackNormal;
sf::Texture buttonBackClick;
sf::Texture buttonFullSoundNormal;
sf::Texture buttonFullSoundClick;
sf::Texture buttonNullSoundNormal;
sf::Texture buttonNullSoundClick;
sf::Texture textureBack;
sf::Texture textureBackSecond;
sf::Texture backgroundFirst;
sf::Texture backgroundSecond;

void loadTextures() {
	if (!backgroundSecond.loadFromFile("backgroundTexture/monitorMain1.png") ||
		!backgroundFirst.loadFromFile("style/styleBack.png") ||
		!textureBack.loadFromFile("backgroundTexture/menuTextureBackground5.png") ||
		!textureBackSecond.loadFromFile("backgroundTexture/menuTextureBackground7.png") || 
		!buttonBackNormal.loadFromFile("backgroundTexture/layer3.png") ||
		!buttonBackClick.loadFromFile("backgroundTexture/layer4.png") ||
		!buttonFullSoundNormal.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon1.png") ||
		!buttonFullSoundClick.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon12.png") ||
		!buttonNullSoundNormal.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon2.png") ||
		!buttonNullSoundClick.loadFromFile("backgroundTexture/secondSoundTexture/Second_soundIcon21.png")) {
		std::cerr << "Error loading image file" << std::endl;
		return;
	}
}