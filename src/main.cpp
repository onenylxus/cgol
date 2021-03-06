// Include
#include "include.h"
#include "cell.h"
#include "map.h"

/* ------------------------ division ------------------------ */

// Main function
int main(int argv, char **args) {
  // Construct
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error: SDL failed to initialize\nSDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Window *window = SDL_CreateWindow("Conway's Game of Life", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, 0);
  if (!window) {
    std::cout << "Error: Failed to open window\nSDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }

  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer) {
    std::cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_Event event;

  bool isRunning = true;
  Map* map = new Map(WINDOW_WIDTH / CELL_SIZE, WINDOW_HEIGHT / CELL_SIZE);

  // Update loop
  while (isRunning) {
    // Events
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          isRunning = false;
          break;

        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            map->toggleCell(event.button.x, event.button.y);
          }

        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              isRunning = false;
              break;

            case SDLK_SPACE:
              map->setRunning(!map->getRunning());
              break;

            case SDLK_UP:
              map->setOffset(Direction::topMiddle);
              break;

            case SDLK_DOWN:
              map->setOffset(Direction::bottomMiddle);
              break;

            case SDLK_LEFT:
              map->setOffset(Direction::middleLeft);
              break;

            case SDLK_RIGHT:
              map->setOffset(Direction::middleRight);
              break;
          }
          break;
      }
    }

    // Update map
    map->iterate();
    map->draw(renderer);
  }

  // Destruct
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
