#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <signal.h>

void ignore(int a) {

}

int main() {
  char filename[30];
  sprintf(filename, "test.sh");
  int fd1[2];
  int fd2[2];

  signal(SIGHUP, ignore);
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

    char *args[] = {"test.sh", NULL};
    execl("/bin/bash", "/bin/bash", "/home/fexolm/test.sh", NULL);

    exit(1);
  } else {
    sleep(1);
    close(fd1[0]);
    close(fd2[1]);

    int pout = fd1[1];
    int pin = fd2[0];

    char res[30];
    ssize_t size = read(pin, res, 50);

    printf("%s", res);
  }
  return 0;
}