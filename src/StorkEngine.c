#include "StorkEngine.h"
#include "StorkEngine_Graphics.h"
#include "StorkEngine_def.h"

void StorkEngine_PerformGameTick(SDL_Renderer *ren, StorkEngine_GameData data) {
  for (size_t y = 0; y < data->map->height; y++) {
    for (size_t x = 0; x < data->map->width; x++) {
      StorkEngine_DrawCell(ren, StorkEngine_GetMapCell(data->map, x, y), x, y);
    }
  }
  StorkEngine_ProcessUserInput(data);
}

StorkEngine_GameData StorkEngine_CreateGameData() {
  size_t map_size = sizeof(struct __GameMap) +
      STORK_ENGINE_MAP_WIDTH*STORK_ENGINE_MAP_HEIGHT*sizeof(StorkEngine_CellType);

  void *mem = malloc(
      sizeof(struct __GameData)
          + map_size
          + sizeof(StorkEngine_Strategy)*STORK_ENGINE_PLAYER_COUNT);
  StorkEngine_GameData data = mem;
  mem += sizeof(struct __GameData);
  data->map = StorkEngine_ConstructGameMap(mem);
  mem += map_size;
  data->strategies = mem;
  return data;
}

void StorkEngine_DestroyGameData(StorkEngine_GameData data) {
  free(data);
}

void StorkEngine_GameInit(StorkEngine_GameData data) {
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    int x = rand()%STORK_ENGINE_MAP_WIDTH,
        y = rand()%STORK_ENGINE_MAP_HEIGHT;

    data->strategies[i].point.x;
    data->strategies[i].point.y;
    data->strategies[i].active = false;

    StorkEngine_SetMapCell(data->map, (size_t) x, (size_t) y, StorkEngineCT_Player1 << i);
  }
}
