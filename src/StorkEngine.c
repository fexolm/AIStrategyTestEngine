#include "StorkEngine.h"
#include "StorkEngine_Graphics.h"
#include "StorkEngine_def.h"

void StorkEngine_PerformGameTick(SDL_Renderer *ren, StorkEngine_GameData data) {
  StorkEngine_UpdateProjectiles(data);

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

  data->projectiles.head = NULL;
  return data;
}

void StorkEngine_DestroyGameData(StorkEngine_GameData data) {
  free(data);
}

void StorkEngine_GameInit(StorkEngine_GameData data) {
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    int x = rand()%STORK_ENGINE_MAP_WIDTH,
        y = rand()%STORK_ENGINE_MAP_HEIGHT;

    data->strategies[i].object.point.x = (size_t) x;
    data->strategies[i].object.point.y = (size_t) y;
    data->strategies[i].active = false;
    data->strategies[i].object.rotation = StorkEngineCMDR_Left;
    data->strategies[i].object.cellType = StorkEngineCT_Player1 << i;

    StorkEngine_SetMapCell(data->map, (size_t) x, (size_t) y, StorkEngineCT_Player1 << i);
  }
}

void StorkEngine_MoveObject(StorkEngine_GameMap map, StorkEngine_MapObject *obj, StorkEngine_Point point) {
  StorkEngine_SetMapCell(map, (size_t) obj->point.x, (size_t) obj->point.y, StorkEngineCT_Empty);
  obj->point = point;
  StorkEngine_SetMapCell(map, (size_t) obj->point.x, (size_t) obj->point.y, obj->cellType);
}

StorkEngine_Point StorkEngine_GetMovePoint(StorkEngine_MapObject *obj) {
  StorkEngine_Point point = obj->point;
  switch (obj->rotation) {
  case StorkEngineCMDR_Right:point.x++;
    break;
  case StorkEngineCMDR_Left:point.x--;
    break;
  case StorkEngineCMDR_Up:point.y--;
    break;
  case StorkEngineCMDR_Down:point.y++;
    break;
  }
  return point;
}