// Include
#include "Map.h"

/* ------------------------ division ------------------------ */

// Constructor
Map::Map(int width, int height) {
  // Set properties
  this->width = width;
  this->height = height;
  this->offsetX = fmin((WINDOW_WIDTH / CELL_SIZE - width) / 2, 0);
  this->offsetY = fmin((WINDOW_HEIGHT / CELL_SIZE - height) / 2, 0);

  // Generate cells
  for (int i = 0; i < this->width * this->height; i++) {
    this->cells.push_back(new Cell(0));
  }
}

// Destructor
Map::~Map() {
  this->cells.clear();
}

/* ------------------------ division ------------------------ */

// Get running state
bool Map::getRunning() {
  return this->running;
}

// Get ticks
int Map::getTicks() {
  return this->ticks;
}

// Get horizontal offset
int Map::getOffsetX() {
  return this->offsetX;
}

// Get vertical offset
int Map::getOffsetY() {
  return this->offsetY;
}

// Set running state
void Map::setRunning(bool state) {
  this->running = state;
  std::cout << "State: " << (this->running ? "true" : "false") << std::endl;
}

// Set offset
void Map::setOffset(Direction dir) {
  switch (dir) {
    case Direction::topMiddle:
      this->offsetY--;
      this->expand(this->offsetY < 0, false, false, false);
      break;

    case Direction::bottomMiddle:
      this->offsetY++;
      this->expand(false, this->offsetY + WINDOW_HEIGHT / CELL_SIZE >= this->height, false, false);
      break;

    case Direction::middleLeft:
      this->offsetX--;
      this->expand(false, false, this->offsetX < 0, false);
      break;

    case Direction::middleRight:
      this->offsetX++;
      this->expand(false, false, false, this->offsetX + WINDOW_WIDTH / CELL_SIZE >= this->height);
      break;
  }
  std::cout << "Offset: (" << this->offsetX << ", " << this->offsetY << ")" << std::endl;
}

/* ------------------------ division ------------------------ */

// Iterate function
void Map::iterate() {
  // Reject if state
  if (!this->running) {
    return;
  }

  // Expand map if necessary
  bool expandTop = false;
  bool expandBottom = false;
  bool expandLeft = false;
  bool expandRight = false;

  for (int i = 0; i < this->cells.size(); i++) {
    Cell *cell = this->cells[i];

    if (cell->getSelf() > 0) {
      expandTop |= this->isTop(i);
      expandBottom |= this->isBottom(i);
      expandLeft |= this->isLeft(i);
      expandRight |= this->isRight(i);
    }
  }
  this->expand(expandTop, expandBottom, expandLeft, expandRight);

  // Set neighbour values
  for (int i = 0; i < this->cells.size(); i++) {
    Cell *cell = this->cells[i];

    if (!this->isTop(i)) {
      if (!this->isLeft(i) && this->cells[i - this->width - 1]->getSelf() > 0) {
        cell->addNeighbour(Direction::topLeft);
      }
      if (this->cells[i - this->width]->getSelf() > 0) {
        cell->addNeighbour(Direction::topMiddle);
      }
      if (!this->isRight(i) && this->cells[i - this->width + 1]->getSelf() > 0) {
        cell->addNeighbour(Direction::topRight);
      }
    }
    if (!this->isLeft(i) && this->cells[i - 1]->getSelf() > 0) {
      cell->addNeighbour(Direction::middleLeft);
    }
    if (!this->isRight(i) && this->cells[i + 1]->getSelf() > 0) {
      cell->addNeighbour(Direction::middleRight);
    }
    if (!this->isBottom(i)) {
      if (!this->isLeft(i) && this->cells[i + this->width - 1]->getSelf() > 0) {
        cell->addNeighbour(Direction::bottomLeft);
      }
      if (this->cells[i + this->width]->getSelf() > 0) {
        cell->addNeighbour(Direction::bottomMiddle);
      }
      if (!this->isRight(i) && this->cells[i + this->width + 1]->getSelf() > 0) {
        cell->addNeighbour(Direction::bottomRight);
      }
    }
  }

  // Determine self state
  for (int i = 0; i < this->cells.size(); i++) {
    Cell *cell = this->cells[i];
    int count = cell->getNeighbourCount();
    cell->setValue(count == 3 || (count == 2 && cell->getSelf() > 0));
  }

  // Finalize
  this->ticks++;
  SDL_Delay(ceilf(1000.0f / TICKS_PER_SECOND));
}

// Expand function
void Map::expand(bool top, bool bottom, bool left, bool right) {
  // Expand top
  if (top) {
    std::vector<Cell *> data;
    this->height++;
    this->offsetY++;

    int ptr = 0;
    for (int i = 0; i < this->width * this->height; i++) {
      data.push_back(!this->isTop(i) ? this->cells[ptr++] : new Cell(0));
    }
    this->cells = data;
  }

  // Expand bottom
  if (bottom) {
    std::vector<Cell *> data;
    this->height++;

    int ptr = 0;
    for (int i = 0; i < this->width * this->height; i++) {
      data.push_back(!this->isBottom(i) ? this->cells[ptr++] : new Cell(0));
    }
    this->cells = data;
  }

  // Expand left
  if (left) {
    std::vector<Cell *> data;
    this->width++;
    this->offsetX++;

    int ptr = 0;
    for (int i = 0; i < this->width * this->height; i++) {
      data.push_back(!this->isLeft(i) ? this->cells[ptr++] : new Cell(0));
    }
    this->cells = data;
  }

  // Expand right
  if (right) {
    std::vector<Cell *> data;
    this->width++;

    int ptr = 0;
    for (int i = 0; i < this->width * this->height; i++) {
      data.push_back(!this->isRight(i) ? this->cells[ptr++] : new Cell(0));
    }
    this->cells = data;
  }
}

// Draw function
void Map::draw(SDL_Renderer* renderer) {
  // Clear window
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  // Draw grid lines
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int i = 0; i < WINDOW_WIDTH / CELL_SIZE; i++) {
    SDL_RenderDrawLine(renderer, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_HEIGHT);
  }
  for (int j = 0; j < WINDOW_HEIGHT / CELL_SIZE; j++) {
    SDL_RenderDrawLine(renderer, 0, j * CELL_SIZE, WINDOW_WIDTH, j * CELL_SIZE);
  }
  if (WINDOW_WIDTH % CELL_SIZE == 0) {
    SDL_RenderDrawLine(renderer, WINDOW_WIDTH - 1, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT);
  }
  if (WINDOW_HEIGHT % CELL_SIZE == 0) {
    SDL_RenderDrawLine(renderer, 0, WINDOW_HEIGHT - 1, WINDOW_WIDTH, WINDOW_HEIGHT - 1);
  }

  // Draw map
  for (int j = 0; j < WINDOW_HEIGHT / CELL_SIZE; j++) {
    for (int i = 0; i < WINDOW_WIDTH / CELL_SIZE; i++) {
      // Offset coordinates
      int u = i + this->offsetX;
      int v = j + this->offsetY;

      // Skip bad positions
      if (u < 0 || u >= fmin(this->width, this->offsetX + WINDOW_WIDTH / CELL_SIZE)) {
        continue;
      }
      if (v < 0 || v >= fmin(this->height, this->offsetY + WINDOW_HEIGHT / CELL_SIZE)) {
        continue;
      }

      // Draw live cells
      if (this->cells[v * this->width + u]->getSelf() > 0) {
        SDL_Rect rect;
        rect.x = i * CELL_SIZE;
        rect.y = j * CELL_SIZE;
        rect.w = rect.h = CELL_SIZE;
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }

  // Display
  SDL_RenderPresent(renderer);
}

// Toggle cell
void Map::toggleCell(int x, int y) {
  // Reject toggle when running
  if (this->running) {
    return;
  }

  // Offset coordinates
  int u = x / CELL_SIZE + this->offsetX;
  int v = y / CELL_SIZE + this->offsetY;

  std::cout << "Toggle position: (" << u << ", " << v << ")" << std::endl;
  std::cout << "Dimensions: " << this->width << "x" << this->height << std::endl;

  // Skip bad positions
  if (u < 0 || u >= this->width) {
    return;
  }
  if (v < 0 || v >= this->height) {
    return;
  }

  // Toggle cell
  Cell *cell = this->cells[v * this->width + u];
  cell->setValue(!cell->getSelf());
}

/* ------------------------ division ------------------------ */

// Check for top row
bool Map::isTop(int index) {
  return index / this->width == 0;
}

// Check for bottom row
bool Map::isBottom(int index) {
  return index / this->width == this->height - 1;
}

// Check for left column
bool Map::isLeft(int index) {
  return index % this->width == 0;
}

// Check for right column
bool Map::isRight(int index) {
  return (index + 1) % this->width == 0;
}