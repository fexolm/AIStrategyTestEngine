#pragma once
#include <SDL2/SDL.h>
#include "GameMap.h"

void StorkEngine_DrawCell(SDL_Renderer *ren, StorkEngine_CellType cellType, size_t x, size_t y);