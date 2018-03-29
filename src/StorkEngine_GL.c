#include "StorkEngine_GL.h"
#include <unistd.h>
#include <sys/prctl.h>
#include <signal.h>

void StorkEngine_GameInit(StorkEngine_GameData data) {
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    int x = rand()%STORK_ENGINE_MAP_WIDTH,
        y = rand()%STORK_ENGINE_MAP_HEIGHT;

    data->players[i].point.x;
    data->players[i].point.y;
    data->players[i].active = false;

    StorkEngine_SetMapCell(data->map, (size_t) x, (size_t) y, StorkEngineCT_Player1 << i);
  }
}

void StorkEngine_ConnectStrategies(StorkEngine_GameData data) {
  char filename[30];
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    sprintf(filename, "player%d.sh", i);
    int inpipefd[2];
    int outpipefd[2];

    pipe(inpipefd);
    pipe(outpipefd);
    pid_t pid = fork();
    if (!pid) {
      dup2(outpipefd[0], STDIN_FILENO);
      dup2(inpipefd[1], STDOUT_FILENO);

      prctl(PR_SET_PDEATHSIG, SIGTERM);

      execl(filename, NULL, NULL);

      exit(1);
    }

    close(outpipefd[0]);
    close(inpipefd[1]);

    data->players[i].pout = outpipefd[1];
    data->players[i].pin = inpipefd[0];
  }
}