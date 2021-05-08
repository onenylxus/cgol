// Pragma and include
#pragma once
#include "include.h"

/* ------------------------ division ------------------------ */

// Cell class
class Cell {
  // Constructor and destructor
  public:
    Cell(int value);
    ~Cell();

  // Properties
  private:
    int value;

  // Methods
  public:
    int getValue();
    int getSelf();
    int getNeighbourCount();
    void setValue(int value);
    void addNeighbour(Direction dir);
};
