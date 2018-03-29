#pragma once
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

typedef struct __Player {
  StorkEngine_Point point;
  bool active;
  int pin;
  int pout;
} StorkEngine_Player;

typedef struct __Projectile {
  StorkEngine_Point point;
} StorkEngine_Projectile;

struct __GameData {
  StorkEngine_GameMap map;
  StorkEngine_Player *players;
};

typedef struct __GameData *StorkEngine_GameData;