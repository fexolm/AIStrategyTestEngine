#include <SDL2/SDL.h>
#include <stdbool.h>
#include <time.h>
#include "StorkEngine.h"
#include "StorkEngine_def.h"
int main() {
  srand((unsigned int) time(NULL));

  if (SDL_Init(SDL_INIT_VIDEO)!=0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());;
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("StorkEngine", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
  if (!win) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!ren) {
    printf("SDL_CreateRenderer Error: %s", SDL_GetError());
    return 1;
  }

  bool running = true;

  Uint32 ticks = SDL_GetTicks();

  StorkEngine_GameData gameData = StorkEngine_CreateGameData();

  StorkEngine_GameInit(gameData);

  StorkEngine_ConnectStrategies(gameData);

  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)
        && event.type==SDL_KEYDOWN
        && event.key.keysym.sym==SDLK_ESCAPE)
      running = false;

    Uint32 now = SDL_GetTicks();
    if (now - ticks < STORK_ENGINE_TICK_INTERVAL)
      continue;
    ticks = now;

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
    SDL_RenderClear(ren);

    StorkEngine_PerformGameTick(ren, gameData);

    SDL_RenderPresent(ren);
  }

  StorkEngine_DestroyGameData(gameData);

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();

  return 0;
}

