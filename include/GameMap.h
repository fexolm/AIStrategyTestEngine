#pragma once
#include <stddef.h>
#include "StorkEngine_def.h"
#include "StorkEngine_Data.h"
extern const size_t StorkEngine_MapSize;

StorkEngine_GameMap StorkEngine_ConstructGameMap(void *mem);

StorkEngine_CellType StorkEngine_GetMapCell(const StorkEngine_GameMap map, size_t x, size_t y);

void StorkEngine_SetMapCell(StorkEngine_GameMap map, size_t x, size_t y, StorkEngine_CellType type);
