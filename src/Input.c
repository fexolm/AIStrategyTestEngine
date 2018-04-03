#include <unistd.h>
#include "StorkEngine.h"
#include "StorkEngine_def.h"

static void __Move(StorkEngine_Strategy *strategy, StorkEngine_GameData data, StorkEngine_Command cmd) {
  StorkEngine_Point point = strategy->point;
  switch (strategy->rotation) {
  case StorkEngineCMDR_Right:point.x++;
    break;
  case StorkEngineCMDR_Left:point.x--;
    break;
  case StorkEngineCMDR_Up:point.y--;
    break;
  case StorkEngineCMDR_Down:point.y++;
    break;
  }

  if (StorkEngine_GetMapCell(data->map, point.x, point.y)==StorkEngineCT_Empty) {
    StorkEngine_SetMapCell(data->map, (size_t) strategy->point.x, (size_t) strategy->point.y, StorkEngineCT_Empty);
    strategy->point = point;
    StorkEngine_SetMapCell(data->map, (size_t) strategy->point.x, (size_t) strategy->point.y, strategy->cellType);
  }
}

static void __Shoot(StorkEngine_Strategy *strategy, StorkEngine_GameData data, StorkEngine_Command cmd) {

}

static void __Rotate(StorkEngine_Strategy *strategy, StorkEngine_GameData data, StorkEngine_Command cmd) {
  strategy->rotation = *((StorkEngine_CmdRotateType *) cmd->commandPrivate);
}

static void __ProcessCommand(StorkEngine_Strategy *strategy, StorkEngine_GameData data, StorkEngine_Command cmd) {
  switch (cmd->type) {

  case StorkEngineCMD_Nope:break;
  case StorkEngineCMD_Move:__Move(strategy, data, cmd);
    break;
  case StorkEngineCMD_Shoot:__Shoot(strategy, data, cmd);
    break;
  case StorkEngineCMD_Rotate:__Rotate(strategy, data, cmd);
    break;
  }
}

static void __WriteGameState(StorkEngine_Strategy *strategy, StorkEngine_GameData data) {
  char buf[10];
  sprintf(buf, "%d ", STORK_ENGINE_MAP_HEIGHT*STORK_ENGINE_MAP_WIDTH);
  write(strategy->pout, buf, strlen(buf));

  for (int y = 0; y < STORK_ENGINE_MAP_HEIGHT; y++) {
    for (int x = 0; x < STORK_ENGINE_MAP_WIDTH; x++) {
      sprintf(buf, "%d ", StorkEngine_GetMapCell(data->map, (size_t) x, (size_t) y));
      write(strategy->pout, buf, strlen(buf));
    }
  }
}

static void __ProcessUserInput(StorkEngine_Strategy *strategy, StorkEngine_GameData data) {
  char buf[128];
  read(strategy->pin, buf, 128);
  StorkEngine_Command cmd = StorkEngine_BuildCommand(buf);
  __ProcessCommand(strategy, data, cmd);
}

void StorkEngine_ProcessUserInput(StorkEngine_GameData data) {
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    __WriteGameState(&data->strategies[i], data);
    __ProcessUserInput(&data->strategies[i], data);
  }
}