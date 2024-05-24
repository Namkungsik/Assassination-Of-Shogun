#include "PlayerAnimate.h"

// 플레이어 멈춤
void __Idle(HDC dcScreen, OBJ_MON* g_obj)
{
	char strName[24];

	__SetSprSurface(&(g_obj[0].g_sfPlayer[0]), RGB(84, 109, 142));
	wsprintf(strName, "NinjaIdle.bmp");
	g_obj[0].g_sfPlayer[0].hBmp = __MakeDDBFromDIB(dcScreen, strName);
	__LoadSurface(dcScreen, &(g_obj[0].g_sfPlayer[0]));

	__SetSprSurface(&(g_obj[6].g_sfPlayer[0]), RGB(84, 109, 142));
	wsprintf(strName, "NinjaLIdle.bmp");
	g_obj[6].g_sfPlayer[0].hBmp = __MakeDDBFromDIB(dcScreen, strName);
	__LoadSurface(dcScreen, &(g_obj[6].g_sfPlayer[0]));

}

// 플레이어 움직임
void __Move(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];

	for (i = 0; i < 3; i++)
	{
		__SetSprSurface(&(g_obj[1].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "NinjaRunning%d.bmp", i + 1);
		g_obj[1].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[1].g_sfPlayer[i]));
	}

	for (i = 0; i < 3; i++)
	{
		__SetSprSurface(&(g_obj[7].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "NinjaLRunning%d.bmp", i + 1);
		g_obj[7].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[7].g_sfPlayer[i]));
	}
}

// 플레이어 점프
void __Jump(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];

	for (i = 0; i < 2; i++)
	{
		__SetSprSurface(&(g_obj[2].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "NinjaJump%d.bmp", i + 1);
		g_obj[2].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[2].g_sfPlayer[i]));
	}

	for (i = 0; i < 2; i++)
	{
		__SetSprSurface(&(g_obj[9].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "NinjaRJump%d.bmp", i + 1);
		g_obj[9].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[9].g_sfPlayer[i]));
	}
}

// 플레이어 더블 점프
void __DJump(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];

	for (i = 0; i < 5; i++)
	{
		__SetSprSurface(&(g_obj[4].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "DJump%d.bmp", i + 1);
		g_obj[4].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[4].g_sfPlayer[i]));
	}
	for (i = 0; i < 5; i++)
	{
		__SetSprSurface(&(g_obj[10].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "LDJump%d.bmp", i + 1);
		g_obj[10].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[10].g_sfPlayer[i]));
	}
}

// 플레이어 공격
void __Attack(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];


	for (i = 0; i < 4; i++)
	{
		__SetSprSurface(&(g_obj[3].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "NinjaAttack%d.bmp", i + 1);
		g_obj[3].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[3].g_sfPlayer[i]));
	}

	for (i = 0; i < 4; i++)
	{
		__SetSprSurface(&(g_obj[8].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "NinjaLAttack%d.bmp", i + 1);
		g_obj[8].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[8].g_sfPlayer[i]));
	}
}


// 플레이어 수리검 공격
void __ShurikenAttack(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];

	for (i = 0; i < 3; i++)
	{
		__SetSprSurface(&(g_obj[5].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShurikenAttack%d.bmp", i + 1);
		g_obj[5].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[5].g_sfPlayer[i]));
	}
}

void __Shuriken(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];

	for (i = 0; i < 4; i++)
	{
		__SetSprSurface(&(g_obj[0].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "Shuriken%d.bmp", i + 1);
		g_obj[0].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[0].g_sfPlayer[i]));
	}
}
