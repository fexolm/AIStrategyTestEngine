#include <SDL2/SDL.h>

int event_handler(void *userdata, SDL_Event *event);

int main() {
  if (SDL_Init(SDL_INIT_VIDEO)!=0) {
    printf("SDL_Init Error: %s\n", SDL_GetError());;
    return 1;
  }

  SDL_Window *win = SDL_CreateWindow("AIStrategyTestEngine!", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
  if (!win) {
    printf("SDL_CreateWindow Error: %s\n", SDL_GetError());
    return 1;
  }

  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!ren) {
    printf("SDL_CreateRenderer Error: %s", SDL_GetError());
    return 1;
  }

  SDL_AddEventWatch(event_handler, NULL);

  SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
  SDL_RenderClear(ren);
  SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
  for (int i = 0; i < 800; ++i)
    SDL_RenderDrawPoint(ren, i, i*3/4);

  SDL_Rect rect;
  rect.x = 100;
  rect.y = 100;
  rect.h = 500;
  rect.w = 500;

  SDL_RenderFillRect(ren, &rect);

  SDL_RenderPresent(ren);

  SDL_Event event;

  while (1) {
    if (SDL_PollEvent(&event) && event.type==SDL_QUIT)
      break;
    SDL_RenderPresent(ren);
  }

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
  SDL_Quit();
  return 0;
}

int event_handler(void *userdata, SDL_Event *event) {
  if (event->type==SDL_KEYDOWN) {
    if (event->key.keysym.sym==SDLK_ESCAPE) {
      SDL_Event exitEvent;
      exitEvent.type = SDL_QUIT;
      SDL_PushEvent(&exitEvent);
      return 1;
    }
  }
  return 0;
}