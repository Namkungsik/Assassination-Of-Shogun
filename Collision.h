#include <windows.h>
#include "GraphicEngine.h"

BOOL CheckCollision(RECT rect1, RECT rect2);

void HandleCollision(HDC hdc, RECT rect1, RECT rect2);

RECT GetSpriteRect(int x, int y, SURFACEINFO* psInfo);

RECT __DrawHitBox(HDC dcScreen, OBJ_MON* g_obj, int x, int y, int spriteNum);