#pragma once

typedef enum __CommandType {
  StorkEngineCMD_Nope = 0,
  StorkEngineCMD_Move = 1,
  StorkEngineCMD_Shoot = 2,
  StorkEngineCMD_Rotate = 3
} StorkEngine_CommandType;

typedef enum __RotateDirecton {
  StorkEngineCMDR_Right = 0,
  StorkEngineCMDR_Left = 1,
  StorkEngineCMDR_Up = 2,
  StorkEngineCMDR_Down = 3
} StorkEngine_CmdRotateType;

struct __Command {
  StorkEngine_CommandType type;
  void *commandPrivate;
};

typedef struct __Command *StorkEngine_Command;

StorkEngine_Command StorkEngine_BuildCommand(const char *const str);

void StorkEngine_DestroyCommand(StorkEngine_Command cmd);

