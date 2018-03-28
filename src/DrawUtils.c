#include "DrawUtils.h"

void StorkEngine_DrawCell(SDL_Renderer *ren, StorkEngine_CellType cellType, size_t x, size_t y) {
  switch (cellType) {
  case StorkEngineCT_Empty:SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
    break;
  case StorkEngineCT_Wall1HP:SDL_SetRenderDrawColor(ren, 184, 22, 22, 255);
    break;
  case StorkEngineCT_Wall2HP:SDL_SetRenderDrawColor(ren, 128, 11, 11, 255);
    break;
  case StorkEngineCT_Wall3HP:SDL_SetRenderDrawColor(ren, 87, 7, 7, 255);
    break;
  case StorkEngineCT_Wall4HP:SDL_SetRenderDrawColor(ren, 51, 5, 5, 255);
    break;
  case StorkEngineCT_Player1:SDL_SetRenderDrawColor(ren, 17, 255, 0, 255);
    break;
  case StorkEngineCT_Player2:SDL_SetRenderDrawColor(ren, 242, 255, 0, 255);
    break;
  case StorkEngineCT_Player3:SDL_SetRenderDrawColor(ren, 13, 0, 255, 255);
    break;
  case StorkEngineCT_Player4:SDL_SetRenderDrawColor(ren, 225, 0, 255, 255);
    break;
  }

  SDL_Rect rect;
  rect.x = (int) (x* STORK_ENGINE_CELL_SIZE);
  rect.y = (int) (y* STORK_ENGINE_CELL_SIZE);
  rect.h = 20;
  rect.w = 20;

  SDL_RenderFillRect(ren, &rect);
}
