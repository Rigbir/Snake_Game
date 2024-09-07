#pragma once
#include <SFML/Graphics.hpp>
#include "gameState.h"

extern int cellSize;
extern int rows;
extern int cols;
extern int foodIndex;  
extern int snakeLength;

enum direction { right, left, up, down };
extern direction dir;

enum speed { first = 30, second = 50, third = 100, fourth = 150, add = 75 };
extern speed sp;

extern bool checkButton;
extern bool checkSound;
extern bool checkEnd;
extern bool isStyleChosen;
extern bool win;
extern bool startKey;

extern sf::Text textTime;
extern sf::Clock levelTimer;

extern int timeLevel;
extern int foodForNextLevel;

extern char input;
extern char inputArcad;
extern char inputStyle;

extern int firstRecord;
extern int secondRecord;
extern int thirdRecord;
extern int fourthRecord;
extern int dynamicRecord;

extern int headX;
extern int headY;
extern int offsetX;
extern int offsetY;

extern gameState state;