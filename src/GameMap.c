#include <stdlib.h>
#include "StorkEngine.h"
#include "StorkEngine_def.h"

void __fill_map(StorkEngine_GameMap map);

const size_t StorkEngine_MapSize = sizeof(struct __GameMap)
    + sizeof(StorkEngine_CellType)*STORK_ENGINE_MAP_WIDTH*STORK_ENGINE_MAP_HEIGHT;

StorkEngine_GameMap StorkEngine_ConstructGameMap(void *mem) {
  StorkEngine_GameMap map = mem;
  map->width = STORK_ENGINE_MAP_WIDTH;
  map->height = STORK_ENGINE_MAP_HEIGHT;
  mem += sizeof(struct __GameMap);
  map->cells = mem;
  __fill_map(map);
  return map;
}

StorkEngine_CellType StorkEngine_GetMapCell(const StorkEngine_GameMap map, size_t x, size_t y) {
  return map->cells[y*map->width + x];
}

void StorkEngine_SetMapCell(StorkEngine_GameMap map, size_t x, size_t y, StorkEngine_CellType type) {
  map->cells[y*map->width + x] = type;
}

void __fill_map(StorkEngine_GameMap map) {
  for (size_t i = 0; i < map->height; i++) {
    for (size_t j = 0; j < map->width; j++) {
      StorkEngine_SetMapCell(map, j, i, StorkEngineCT_Empty);
    }
  }

  for (size_t i = 0; i < map->width; i++) {
    StorkEngine_SetMapCell(map, i, 0, StorkEngineCT_Wall4HP);
    StorkEngine_SetMapCell(map, i, map->width - 1, StorkEngineCT_Wall4HP);
  }

  for (size_t i = 0; i < map->height; i++) {
    StorkEngine_SetMapCell(map, 0, i, StorkEngineCT_Wall4HP);
    StorkEngine_SetMapCell(map, map->height - 1, i, StorkEngineCT_Wall4HP);
  }

  for (int i = 0; i < 400; i++) {
    int x = rand()%STORK_ENGINE_MAP_WIDTH, y = rand()%STORK_ENGINE_MAP_HEIGHT;
    StorkEngine_SetMapCell(map, x, y, StorkEngineCT_Wall4HP);
  }
}
