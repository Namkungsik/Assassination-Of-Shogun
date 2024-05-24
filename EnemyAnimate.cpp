#include "EnemyAnimate.h"

void __ShogunIdle(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];

	for (i = 0; i < 3; i++)
	{
		__SetSprSurface(&(g_obj[0].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunIdle%d.bmp", i + 1);
		g_obj[0].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[0].g_sfPlayer[i]));
	}

	for (i = 0; i < 3; i++)
	{
		__SetSprSurface(&(g_obj[3].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunRIdle%d.bmp", i + 1);
		g_obj[3].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[3].g_sfPlayer[i]));
	}

}

void __ShogunMove(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];


	for (i = 0; i < 6; i++)
	{
		__SetSprSurface(&(g_obj[1].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunRunning%d.bmp", i + 1);
		g_obj[1].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[1].g_sfPlayer[i]));
	}

	for (i = 0; i < 6; i++)
	{
		__SetSprSurface(&(g_obj[4].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunRRunning%d.bmp", i + 1);
		g_obj[4].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[4].g_sfPlayer[i]));
	}

}

void __ShogunAttack1(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];


	for (i = 0; i < 4; i++)
	{
		__SetSprSurface(&(g_obj[2].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunAttack%d.bmp", i + 1);
		g_obj[2].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[2].g_sfPlayer[i]));
	}

	for (i = 0; i < 4; i++)
	{
		__SetSprSurface(&(g_obj[5].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunRAttack%d.bmp", i + 1);
		g_obj[5].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[5].g_sfPlayer[i]));
	}

}

void __ShogunAttack2(HDC dcScreen, OBJ_MON* g_obj)
{
	int i;
	char strName[24];


	for (i = 0; i < 5; i++)
	{
		__SetSprSurface(&(g_obj[6].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunBAttack%d.bmp", i + 1);
		g_obj[6].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[6].g_sfPlayer[i]));
	}

	for (i = 0; i < 5; i++)
	{
		__SetSprSurface(&(g_obj[8].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunBRAttack%d.bmp", i + 1);
		g_obj[8].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[8].g_sfPlayer[i]));
	}

}

void __ShogunAttack2Effect(HDC dcScreen, OBJ_MON* g_obj)
{
	char strName[24];
	char strName2[25];

	__SetSprSurface(&(g_obj[7].g_sfPlayer[0]), RGB(84, 109, 142));
	wsprintf(strName, "ShogunBAttackEffect.bmp");
	g_obj[7].g_sfPlayer[0].hBmp = __MakeDDBFromDIB(dcScreen, strName);
	__LoadSurface(dcScreen, &(g_obj[7].g_sfPlayer[0]));

	__SetSprSurface(&(g_obj[9].g_sfPlayer[0]), RGB(84, 109, 142));
	wsprintf(strName2, "ShogunBRAttackEffect.bmp");
	g_obj[9].g_sfPlayer[0].hBmp = __MakeDDBFromDIB(dcScreen, strName2);
	__LoadSurface(dcScreen, &(g_obj[9].g_sfPlayer[0]));

}

void __ShogunHit(HDC dcScreen, OBJ_MON* g_obj)
{
	char strName[24];
	int i = 0;

	for (i = 0; i < 3; i++)
	{
		__SetSprSurface(&(g_obj[10].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunHit%d.bmp", i + 1);
		g_obj[10].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[10].g_sfPlayer[i]));
	}

	for (i = 0; i < 3; i++)
	{
		__SetSprSurface(&(g_obj[11].g_sfPlayer[i]), RGB(84, 109, 142));
		wsprintf(strName, "ShogunRHit%d.bmp", i + 1);
		g_obj[11].g_sfPlayer[i].hBmp = __MakeDDBFromDIB(dcScreen, strName);
		__LoadSurface(dcScreen, &(g_obj[11].g_sfPlayer[i]));
	}

}
