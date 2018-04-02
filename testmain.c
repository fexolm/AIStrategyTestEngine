
#include <stdio.h>
#include "StorkEngine_Commands.h"
int main() {
  char *cmd_str = "3 2";

  StorkEngine_Command cmd = StorkEngine_BuildCommand(cmd_str);

  StorkEngine_CommandType *type = (StorkEngine_CommandType *) cmd->commandPrivate;

  printf("%d", *type);
  return 0;
}