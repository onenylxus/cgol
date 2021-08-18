// Include
#include "Cell.h"

/* ------------------------ division ------------------------ */

// Constructor
Cell::Cell(int value) {
  this->value = value;
}

// Destructor
Cell::~Cell() {
  return;
}

/* ------------------------ division ------------------------ */

// Get value
int Cell::getValue() {
  return this->value;
}

// Get self value
int Cell::getSelf() {
  return this->value % 2;
}

// Get neighbour value
int Cell::getNeighbourCount() {
  int value = this->value >> 1;
  int count = 0;

  while (value > 0) {
    count += value % 2 > 0;
    value >>= 1;
  }
  return count;
}

// Set value
void Cell::setValue(int value) {
  this->value = value;
}

// Add neighbour value
void Cell::addNeighbour(Direction dir) {
  this->value |= 1 << dir;
}
