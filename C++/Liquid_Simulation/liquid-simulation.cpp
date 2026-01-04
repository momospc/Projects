#include <SDL2/SDL.h>
#include <cmath>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 600
#define CELL_SIZE 5

#define COLUMNS (SCREEN_WIDTH / CELL_SIZE)
#define ROWS (SCREEN_HEIGHT / CELL_SIZE)

#define EMPTY 0
#define WATER 1
#define SOLID 2

#define MAX_PRESSURE 0.5
#define SPREAD_SPEED 0.5

struct Cell {
  int type;
  double fill; // only for WATER
};

Uint32 COL_BLACK, COL_WHITE, COL_BLUE;

void update_water(Cell *env) {
  for (int y = ROWS - 2; y >= 0; y--) {
    for (int x = 0; x < COLUMNS; x++) {
      int i = x + y * COLUMNS;
      if (env[i].type != WATER || env[i].fill <= 0.0001)
        continue;

      double remaining = env[i].fill;

      // ↓ GRAVITY
      int down = x + (y + 1) * COLUMNS;
      if (env[down].type != SOLID) {
        double space = (env[down].type == WATER) ? (1.0 - env[down].fill) : 1.0;

        double flow = fmin(space, remaining);
        if (flow > 0) {
          env[i].fill -= flow;
          if (env[down].type == EMPTY)
            env[down].type = WATER, env[down].fill = 0;
          env[down].fill += flow;
          remaining -= flow;
        }
      }

      // ↙ ↘ DIAGONAL FALL
      if (remaining > 0) {
        for (int dx = -1; dx <= 1; dx += 2) {
          int nx = x + dx;
          if (nx < 0 || nx >= COLUMNS)
            continue;
          int ni = nx + (y + 1) * COLUMNS;
          if (env[ni].type == SOLID)
            continue;

          double space = (env[ni].type == WATER) ? (1.0 - env[ni].fill) : 1.0;

          double flow = fmin(space, remaining) * 0.7;
          if (flow > 0) {
            env[i].fill -= flow;
            if (env[ni].type == EMPTY)
              env[ni].type = WATER, env[ni].fill = 0;
            env[ni].fill += flow;
            remaining -= flow;
          }
        }
      }

      // ← → PRESSURE SPREAD
      if (remaining > 0) {
        for (int dx = -1; dx <= 1; dx += 2) {
          int nx = x + dx;
          if (nx < 0 || nx >= COLUMNS)
            continue;
          int ni = nx + y * COLUMNS;
          if (env[ni].type == SOLID)
            continue;

          double other = (env[ni].type == WATER) ? env[ni].fill : 0.0;
          double diff = (env[i].fill - other) / 2.0;
          double flow = fmin(diff * SPREAD_SPEED, MAX_PRESSURE);

          if (flow > 0) {
            env[i].fill -= flow;
            if (env[ni].type == EMPTY)
              env[ni].type = WATER, env[ni].fill = 0;
            env[ni].fill += flow;
          }
        }
      }
    }
  }
}

void draw(SDL_Surface *surf, Cell *env) {
  SDL_FillRect(surf, NULL, COL_BLACK);

  for (int y = 0; y < ROWS; y++) {
    for (int x = 0; x < COLUMNS; x++) {
      int i = x + y * COLUMNS;
      SDL_Rect r = {x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE};

      if (env[i].type == SOLID) {
        SDL_FillRect(surf, &r, COL_WHITE);
      } else if (env[i].type == WATER && env[i].fill > 0) {
        int h = (int)(env[i].fill * CELL_SIZE);
        SDL_Rect w = {r.x, r.y + CELL_SIZE - h, CELL_SIZE, h};
        SDL_FillRect(surf, &w, COL_BLUE);
      }
    }
  }
}

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *win =
      SDL_CreateWindow("Realistic Liquid Simulation", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);

  SDL_Surface *surf = SDL_GetWindowSurface(win);

  COL_BLACK = SDL_MapRGB(surf->format, 0, 0, 0);
  COL_WHITE = SDL_MapRGB(surf->format, 255, 255, 255);
  COL_BLUE = SDL_MapRGB(surf->format, 40, 160, 255);

  Cell env[ROWS * COLUMNS];
  for (int i = 0; i < ROWS * COLUMNS; i++) {
    env[i].type = EMPTY;
    env[i].fill = 0.0;
  }

  bool running = true;
  int paint_mode = SOLID;
  SDL_Event e;

  while (running) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        running = false;

      if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
        paint_mode = (paint_mode == SOLID) ? WATER : SOLID;

      if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN) {
        int mx, my;
        Uint32 buttons = SDL_GetMouseState(&mx, &my);
        int x = mx / CELL_SIZE;
        int y = my / CELL_SIZE;

        if (x >= 0 && x < COLUMNS && y >= 0 && y < ROWS) {
          int i = x + y * COLUMNS;

          if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
            env[i].type = paint_mode;
            env[i].fill = (paint_mode == WATER) ? 1.0 : 0.0;
          }

          if (buttons & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
            env[i].type = EMPTY;
            env[i].fill = 0.0;
          }
        }
      }
    }

    update_water(env);
    draw(surf, env);
    SDL_UpdateWindowSurface(win);
    SDL_Delay(16);
  }

  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}
