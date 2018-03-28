#pragma once
#include <SDL_render.h>
#include "GameMap.h"
struct __GameData {
  StorkEngine_GameMap map;
};

typedef struct __GameData *StorkEngine_GameData;

StorkEngine_GameData StorkEngine_CreateGameData();

void StorkEngine_DestroyGameData(StorkEngine_GameData data);

void StorkEngine_PerformGameTick(SDL_Renderer *ren, StorkEngine_GameData data);
