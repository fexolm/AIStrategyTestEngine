#include <unistd.h>
#include <sys/prctl.h>
#include <signal.h>
#include "StorkEngine.h"
#include "StorkEngine_def.h"

static void __connectStrategy(StorkEngine_GameData data, StorkEngine_Strategy *strategy, char *filename) {
  int fd1[2]; // engine -> strategy
  int fd2[2]; // strategy -> engine

  pipe(fd1);
  pipe(fd2);
  pid_t pid = fork();

  if (!pid) {
    close(fd1[1]);
    close(fd2[0]);

    dup2(fd1[0], STDIN_FILENO);
    dup2(fd2[1], STDOUT_FILENO);

    prctl(PR_SET_PDEATHSIG, SIGTERM); // close process if main dead

    char *args[] = {filename, NULL};
    execl("a.out", "a.out", NULL);

    exit(1); // return error if strategy down
  } else {
    close(fd1[0]);
    close(fd2[1]);

    strategy->pout = fd1[1]; // write desc
    strategy->pin = fd2[0]; // read desc
  }
}

void StorkEngine_ConnectStrategies(StorkEngine_GameData data) {
  for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
    char filename[50];
    sprintf(filename, "player%d.sh", i);
    __connectStrategy(data, &data->strategies[i], filename);
  }
}

