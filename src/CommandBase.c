#include <stdlib.h>
#include <stdio.h>
#include "StorkEngine_Commands.h"

StorkEngine_Command StorkEngine_BuildCommand(const char *const str) {
  StorkEngine_Command cmd = malloc(sizeof(StorkEngine_Command));
  sscanf(str, "%d", &cmd->type);
  cmd->commandPrivate = NULL;
  switch (cmd->type) {
  case StorkEngineCMD_Nope:break;
  case StorkEngineCMD_Move:break;
  case StorkEngineCMD_Shoot:break;
  case StorkEngineCMD_Rotate:cmd->commandPrivate = malloc(sizeof(StorkEngine_CmdRotateType));
    sscanf(str, "%d%d", &cmd->type, cmd->commandPrivate);
    break;
  }
  return cmd;
}

void StorkEngine_DestroyCommand(StorkEngine_Command cmd) {
  switch (cmd->type) {
  case StorkEngineCMD_Nope:break;
  case StorkEngineCMD_Move:break;
  case StorkEngineCMD_Shoot:break;
  case StorkEngineCMD_Rotate:free(cmd->commandPrivate);
    break;
  }

  free(cmd);
}