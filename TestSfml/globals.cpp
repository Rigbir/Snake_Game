#include "globals.h"

int cellSize = 35;
int rows = 20;
int cols = 25;
int foodIndex = 0;
int snakeLength = 1;

direction dir = right;
speed sp;

bool checkButton = false;
bool checkSound = false;
bool checkEnd = false;
bool isStyleChosen = false;
bool win = false;
bool startKey = false;

sf::Text textTime;
sf::Clock levelTimer;

int timeLevel = 25;
int foodForNextLevel = 10;

char input;
char inputArcad;
char inputStyle;

int firstRecord;
int secondRecord;
int thirdRecord;
int fourthRecord;
int dynamicRecord;

int headX;
int headY;
int offsetX = 0;
int offsetY = 0;

gameState state;