
#include "StorkEngine.h"
#include "DrawUtils.h"
void StorkEngine_PerformGameTick(SDL_Renderer *ren, StorkEngine_GameData data) {
  for (size_t y = 0; y < data->map->height; y++) {
    for (size_t x = 0; x < data->map->width; x++) {
      StorkEngine_DrawCell(ren, StorkEngine_GetMapCell(data->map, x, y), x, y);
    }
  }
}

extern const size_t StorkEngine_MapSize;

StorkEngine_GameData StorkEngine_CreateGameData() {
  void *mem = malloc(sizeof(struct __GameData) + StorkEngine_MapSize);
  StorkEngine_GameData data = mem;
  mem += sizeof(struct __GameData);
  data->map = StorkEngine_ConstructGameMap(mem);
  return data;
}

void StorkEngine_DestroyGameData(StorkEngine_GameData data) {
  free(data);
}
