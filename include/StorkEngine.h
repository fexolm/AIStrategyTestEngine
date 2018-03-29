#pragma once
#include <SDL_render.h>
#include "GameMap.h"
#include "StorkEngine_GL.h"
#include "StorkEngine_Data.h"

StorkEngine_GameData StorkEngine_CreateGameData();

void StorkEngine_DestroyGameData(StorkEngine_GameData data);

void StorkEngine_PerformGameTick(SDL_Renderer *ren, StorkEngine_GameData data);