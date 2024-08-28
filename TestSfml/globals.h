#pragma once

extern int cellSize;
extern int rows;
extern int cols;
extern int foodIndex;
extern int snakeLength;

extern enum direction { right, left, up, down };
extern direction dir;

extern enum speed { first = 30, second = 50, third = 100, fourth = 150, add = 75 };
extern speed sp;