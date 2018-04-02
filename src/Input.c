#include <unistd.h>
#include "StorkEngine.h"
#include "StorkEngine_def.h"
#include "StorkEngine_Commands.h"

static void __ProcessCommand(StorkEngine_GameData data, StorkEngine_Command cmd) {

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
  __ProcessCommand(data, cmd);
}

void StorkEngine_ProcessUserInput(StorkEngine_GameData data) {
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    __WriteGameState(&data->strategies[i], data);
    __ProcessUserInput(&data->strategies[i], data);
  }
}