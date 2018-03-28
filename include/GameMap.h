#pragma once
#include <stddef.h>
#include "StorkEngine_def.h"

typedef enum __CellType {
  StorkEngineCT_Empty = 1,
  StorkEngineCT_Wall1HP = 2,
  StorkEngineCT_Wall2HP = 4,
  StorkEngineCT_Wall3HP = 8,
  StorkEngineCT_Wall4HP = 16,
  StorkEngineCT_Player1 = 32,
  StorkEngineCT_Player2 = 64,
  StorkEngineCT_Player3 = 128,
  StorkEngineCT_Player4 = 256,
} StorkEngine_CellType;

struct __GameMap {
  size_t width;
  size_t height;
  StorkEngine_CellType *cells;
};

typedef struct __GameMap *StorkEngine_GameMap;

extern const size_t StorkEngine_MapSize;

StorkEngine_GameMap StorkEngine_ConstructGameMap(void *mem);

StorkEngine_CellType StorkEngine_GetMapCell(const StorkEngine_GameMap map, size_t x, size_t y);

void StorkEngine_SetMapCell(StorkEngine_GameMap map, size_t x, size_t y, StorkEngine_CellType type);
