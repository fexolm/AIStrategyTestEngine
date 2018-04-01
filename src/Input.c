#include <unistd.h>
#include "StorkEngine.h"
#include "StorkEngine_def.h"

static void __WriteGameState(StorkEngine_Strategy *strategy, StorkEngine_GameData data) {
  char buf[] = "kek\n";
  write(strategy->pout, buf, strlen(buf) + 1);
}

static void __ProcessUserInput(StorkEngine_Strategy *strategy, StorkEngine_GameData data) {
  char buf[1024];
  read(strategy->pin, buf, 1024);
  sleep(1);
  char *tmp = buf;
  while (*(++tmp)!='\n');
  *tmp = '\0';

  char buf2[1000];
  strcpy(buf2, buf);
  printf("%s", buf2);
}

void StorkEngine_ProcessUserInput(StorkEngine_GameData data) {
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    __WriteGameState(&data->strategies[i], data);
    sleep(1);
    __ProcessUserInput(&data->strategies[i], data);
    sleep(1);
  }
}