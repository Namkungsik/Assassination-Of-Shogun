#include <windows.h>
#include "GraphicEngine.h"
//#include "Collision.h"

#define ID_TM_MAINLOOP	1
#define ID_TM_ANIMATION_PLAYER 2
#define ID_TM_ANIMATION_ENEMY 3

#define JUMP_HEIGHT 5    // 점프 속도
#define GRAVITY_ACCELERATION 3 // 중력 가속도

void __Idle(HDC dcScreen, OBJ_MON* g_obj);

// 플레이어 움직임
void __Move(HDC dcScreen, OBJ_MON* g_obj);

// 플레이어 점프
void __Jump(HDC dcScreen, OBJ_MON* g_obj);

// 플레이어 더블 점프
void __DJump(HDC dcScreen, OBJ_MON* g_obj);

// 플레이어 공격
void __Attack(HDC dcScreen, OBJ_MON* g_obj);

// 플레이어 수리검 공격
void __ShurikenAttack(HDC dcScreen, OBJ_MON* g_obj);

// 수리검
void __Shuriken(HDC dcScreen, OBJ_MON* g_obj);