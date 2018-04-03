
#include "StorkEngine.h"
#include "StorkEngine_def.h"
static StorkEngine_ProjectileNode *__AllocPNode() {
  return malloc(sizeof(StorkEngine_ProjectileNode));
}

static void __ProcessCollide(StorkEngine_GameData data, StorkEngine_Point point) {
  StorkEngine_CellType type = StorkEngine_GetMapCell(data->map, point.x, point.y);
  if (type & (StorkEngineCT_Player4 | StorkEngineCT_Player3 | StorkEngineCT_Player2 | StorkEngineCT_Player1)) {
    for (int i = 0; i < STORK_ENGINE_PLAYER_COUNT; i++) {
      if (data->strategies[i].object.point.x==point.x && data->strategies[i].object.point.y==point.y) {
        data->strategies[i].dead = true;
        StorkEngine_SetMapCell(data->map, point.x, point.y, StorkEngineCT_Empty);
      }
    }
  }

  if (type & (StorkEngineCT_Wall1HP | StorkEngineCT_Wall2HP | StorkEngineCT_Wall3HP | StorkEn]gineCT_Wall4HP)) {
    StorkEngine_SetMapCell(data->map, point.x, point.y, type >> 1);
  }
}

void StorkEngine_SpawnProjectile(const StorkEngine_Strategy *const p, StorkEngine_GameData data) {
  StorkEngine_Point point = StorkEngine_GetMovePoint(&p->object);
  if (StorkEngine_GetMapCell(data->map, point.x, point.y)!=StorkEngineCT_Empty) {
    __ProcessCollide(data, point);
    return;
  }
  StorkEngine_ProjectileNode *node = __AllocPNode();
  node->projectile.object.cellType = StorkEngineCT_Projectile;
  node->projectile.object.point = point;
  node->projectile.object.rotation = p->object.rotation;
  node->next = data->projectiles.head;
  data->projectiles.head = node;
}

void StorkEngine_RemoveProjectile(StorkEngine_GameData data, StorkEngine_ProjectileNode *node) {
  StorkEngine_ProjectileNode *tmp = data->projectiles.head;
  StorkEngine_Point point = node->projectile.object.point;
  StorkEngine_SetMapCell(data->map, point.x, point.y, StorkEngineCT_Empty);
  for (; tmp && tmp->next && tmp->next!=node; tmp = tmp->next);

  if (tmp && tmp->next) {
    StorkEngine_ProjectileNode *new_next = tmp->next->next;
    free(tmp->next);
    tmp->next = new_next;
  }
}

void StorkEngine_UpdateProjectiles(StorkEngine_GameData data) {
  for (StorkEngine_ProjectileNode *tmp = data->projectiles.head; tmp; tmp = tmp->next) {
    StorkEngine_Point point = StorkEngine_GetMovePoint(&tmp->projectile.object);

    if (StorkEngine_GetMapCell(data->map, point.x, point.y)==StorkEngineCT_Empty) {
      StorkEngine_MoveObject(data->map, &tmp->projectile.object, point);
      continue;
    }

    __ProcessCollide(data, point);
    StorkEngine_RemoveProjectile(data, tmp);
  }
}