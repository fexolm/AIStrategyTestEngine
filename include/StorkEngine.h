#pragma once
#include <SDL_render.h>
#include <stdbool.h>

typedef enum __CellType {
  StorkEngineCT_Empty = 1 << 0,
  StorkEngineCT_Wall1HP = 1 << 1,
  StorkEngineCT_Wall2HP = 1 << 2,
  StorkEngineCT_Wall3HP = 1 << 3,
  StorkEngineCT_Wall4HP = 1 << 4,
  StorkEngineCT_Player1 = 1 << 5,
  StorkEngineCT_Player2 = 1 << 6,
  StorkEngineCT_Player3 = 1 << 7,
  StorkEngineCT_Player4 = 1 << 8,
} StorkEngine_CellType;

struct __GameMap {
  size_t width;
  size_t height;
  StorkEngine_CellType *cells;
};

typedef struct __GameMap *StorkEngine_GameMap;

typedef struct __Point {
  size_t x;
  size_t y;
} StorkEngine_Point;

typedef struct __Strategy {
  StorkEngine_Point point;
  bool active;
  int pin;
  int pout;
  pid_t pid;
} StorkEngine_Strategy;

typedef struct __Projectile {
  StorkEngine_Point point;
} StorkEngine_Projectile;

struct __GameData {
  StorkEngine_GameMap map;
  StorkEngine_Strategy *strategies;
};

typedef struct __GameData *StorkEngine_GameData;

StorkEngine_GameData StorkEngine_CreateGameData();

void StorkEngine_DestroyGameData(StorkEngine_GameData data);

void StorkEngine_PerformGameTick(SDL_Renderer *ren, StorkEngine_GameData data);

void StorkEngine_GameInit(StorkEngine_GameData data);

StorkEngine_GameMap StorkEngine_ConstructGameMap(void *mem);

StorkEngine_CellType StorkEngine_GetMapCell(const StorkEngine_GameMap map, size_t x, size_t y);

void StorkEngine_SetMapCell(StorkEngine_GameMap map, size_t x, size_t y, StorkEngine_CellType type);

void StorkEngine_ConnectStrategies(StorkEngine_GameData data);

void StorkEngine_ProcessUserInput(StorkEngine_GameData data);