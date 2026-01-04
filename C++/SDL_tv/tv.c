#include "SDL2/SDL.h"
#include <SDL2/SDL_stdinc.h>
#include <stdio.h>
#include <stdlib.h>

void print_random_data(SDL_Surface *surface) {
  int num_pixels = surface->w * surface->h;
  Uint32 *pixels = (Uint32 *)surface->pixels;
  for (int i = 0; i < num_pixels; i++) {
    pixels[i] = (Uint32)rand();
  }
}

int main(int argc, char *argv[]) {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window = SDL_CreateWindow("SDL2Test", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, 640, 480, 0);
  SDL_Surface *surface = SDL_GetWindowSurface(window);

  SDL_Event event;
  int running = 1;
  while (running) {
    SDL_PollEvent(&event);
    if (event.type == SDL_QUIT)
      running = 0;
    print_random_data(surface);
    SDL_UpdateWindowSurface(window);
    SDL_Delay(10);
  }
  SDL_Renderer *renderer =
      SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_RenderPresent(renderer);

  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
