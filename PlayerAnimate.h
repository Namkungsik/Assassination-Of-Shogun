#include <windows.h>
#include "GraphicEngine.h"
//#include "Collision.h"

#define ID_TM_MAINLOOP	1
#define ID_TM_ANIMATION_PLAYER 2
#define ID_TM_ANIMATION_ENEMY 3

#define JUMP_HEIGHT 5    // ���� �ӵ�
#define GRAVITY_ACCELERATION 3 // �߷� ���ӵ�

void __Idle(HDC dcScreen, OBJ_MON* g_obj);

// �÷��̾� ������
void __Move(HDC dcScreen, OBJ_MON* g_obj);

// �÷��̾� ����
void __Jump(HDC dcScreen, OBJ_MON* g_obj);

// �÷��̾� ���� ����
void __DJump(HDC dcScreen, OBJ_MON* g_obj);

// �÷��̾� ����
void __Attack(HDC dcScreen, OBJ_MON* g_obj);

// �÷��̾� ������ ����
void __ShurikenAttack(HDC dcScreen, OBJ_MON* g_obj);

// ������
void __Shuriken(HDC dcScreen, OBJ_MON* g_obj);