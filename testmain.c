#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <signal.h>

int main() {
  int fd1[2];
  int fd2[2];

  pipe(fd1);
  pipe(fd2);
  pid_t pid = fork();

  // писать в 1 читать из 0
  if (!pid) {
    close(fd1[1]);
    close(fd2[0]);

    dup2(fd1[0], STDIN_FILENO);
    dup2(fd2[1], STDOUT_FILENO);

    prctl(PR_SET_PDEATHSIG, SIGTERM);

    execl("/bin/bash", "/bin/bash", "player1.sh", NULL);
    execl("a.out", "a.out", NULL);

    exit(1);
  } else {
    close(fd1[0]);
    close(fd2[1]);

    int pout = fd1[1];
    int pin = fd2[0];

    char *kek = NULL;
    size_t len = 0;
    getline(&kek, &len, stdin);

    ssize_t a = write(pout, kek, len);

    char cmd[130];
    char res[1];
    int i;
    for (i = 0; i < 130 && *res!='\n'; i++) {
      read(pin, res, 1);
      cmd[i] = *res;
    }
    cmd[i] = '\0';
    *res = '2';
    i = 0;
    printf("%s", cmd);
  }
  return 0;
}