// Pragma
#pragma once
#include "include.h"
#include "Cell.h"

/* ------------------------ division ------------------------ */

// Map class
class Map {
  // Constructor and destructor
  public:
    Map(int width, int height);
    ~Map();

  // Properties
  private:
    int width;
    int height;
    std::vector<Cell *> cells;

    bool running = false;
    int ticks = 0;
    int offsetX;
    int offsetY;

  // Methods
  public:
    bool getRunning();
    int getTicks();
    int getOffsetX();
    int getOffsetY();
    void setRunning(bool state);
    void setOffset(Direction dir);

    void iterate();
    void expand(bool top, bool bottom, bool left, bool right);
    void draw(SDL_Renderer *renderer);
    void toggleCell(int x, int y);

  private:
    bool isTop(int index);
    bool isBottom(int index);
    bool isLeft(int index);
    bool isRight(int index);
};