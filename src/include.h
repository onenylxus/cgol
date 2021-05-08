// Pragma
#pragma once
#include <SDL2/SDL.h>
#include <cmath>
#include <iostream>
#include <vector>

/* ------------------------ division ------------------------ */

// Window resolution
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

// Directrion enum
enum Direction {
  topLeft = 1,
  topMiddle = 2,
  topRight = 3,
  middleLeft = 4,
  middleRight = 5,
  bottomLeft = 6,
  bottomMiddle = 7,
  bottomRight = 8,
};

// Cell size
const int CELL_SIZE = 20;

// Clock
const int TICKS_PER_SECOND = 5;
