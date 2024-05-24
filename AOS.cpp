#include <windows.h>
#include "GraphicEngine.h"
#include "Collision.h"
#include "PlayerAnimate.h"
#include "EnemyAnimate.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
VOID    CALLBACK MainLoopProc(HWND, UINT, UINT, DWORD);
void __KeyProc(HWND hWnd);
int __TransitionShuriken(int PlayerPosition, int TransitionPlayerPosition);

HINSTANCE g_hInst;
HWND hWndMain;
LPSTR lpszClass = "[ Assassination Of Shogun ]";

SURFACEINFO g_sfBack;			// 버퍼 표면
SURFACEINFO g_sfBG;				// 배경 표면
OBJ_MON		g_objPlayer[14];
OBJ_MON		g_objEnemy[12];
OBJ_MON		g_objItem[3];
OBJ_MON		g_objState[2];

int curX = 0;
int curY = 310;
int shurikenX = 0;
bool RightFace = TRUE;

int EcurX = 0;
int ShogunMaxHealth = 100;
int ShogunCurrentHealth = 100;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance
	, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_SYSMENU | WS_CAPTION, //WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 640, 510,
		NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	hWndMain = hWnd;

	while (TRUE)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT) break;
			DispatchMessage(&Message);
		}
		else
		{
			__KeyProc(hWnd);
			Sleep(10);
		}
	}
	return (int)Message.wParam;
}

//// 일괄 표면 생성
void __Init(HDC dcScreen)
{
	int i;
	char strName[24];

	////
	__CreateBackBuffer(dcScreen, 1000, 480, 32, &g_sfBack);

	////
	__SetImgSurface(&g_sfBG);
	g_sfBG.hBmp = __MakeDDBFromDIB(dcScreen, "NinjaGameBG.bmp");
	__LoadSurface(dcScreen, &g_sfBG);


	__SetSprSurface(&(g_objItem[2].g_sfPlayer[0]), RGB(84, 109, 142));
	wsprintf(strName, "wall.bmp");
	g_objItem[2].g_sfPlayer[0].hBmp = __MakeDDBFromDIB(dcScreen, strName);
	__LoadSurface(dcScreen, &(g_objItem[2].g_sfPlayer[0]));

}

//// 일괄 표면 파괴
void __DestroyAll()
{
	int i;

	// 플레이어 대기 상태
	__ReleaseSurface(&(g_objPlayer[0].g_sfPlayer[0])); // 오른쪽
	__ReleaseSurface(&(g_objPlayer[6].g_sfPlayer[0])); // 왼쪽

	for (i = 0; i < 3; i++) // 플레이어 오른쪽 움직임
	{
		__ReleaseSurface(&(g_objPlayer[1].g_sfPlayer[i]));
	}
	for (i = 0; i < 2; i++) // 플레이어 점프
	{
		__ReleaseSurface(&(g_objPlayer[2].g_sfPlayer[i]));
	}
	for (i = 0; i < 4; i++) // 플레이어 공격
	{
		__ReleaseSurface(&(g_objPlayer[3].g_sfPlayer[i]));
	}
	for (i = 0; i < 5; i++) // 플레이어 더블 점프
	{
		__ReleaseSurface(&(g_objPlayer[4].g_sfPlayer[i]));
	}
	for (i = 0; i < 3; i++) // 플레이어 수리검공격
	{
		__ReleaseSurface(&(g_objPlayer[5].g_sfPlayer[i]));
	}
	for (i = 0; i < 3; i++) // 플레이어 왼쪽 움직임
	{
		__ReleaseSurface(&(g_objPlayer[7].g_sfPlayer[i]));
	}
	for (i = 0; i < 4; i++) // 플레이어 왼쪽 움직임
	{
		__ReleaseSurface(&(g_objPlayer[8].g_sfPlayer[i]));
	}
	for (i = 0; i < 2; i++) // 플레이어 왼쪽 움직임
	{
		__ReleaseSurface(&(g_objPlayer[9].g_sfPlayer[i]));
	}

	for (int i = 0; i < 3; i++) // 쇼군 대기
	{
		__ReleaseSurface(&(g_objEnemy[0].g_sfPlayer[i]));
	}
	for (int i = 0; i < 6; i++) // 쇼군 왼쪽 움직임
	{
		__ReleaseSurface(&(g_objEnemy[1].g_sfPlayer[i]));
	}
	for (int i = 0; i < 4; i++) // 쇼군 공격1
	{
		__ReleaseSurface(&(g_objEnemy[2].g_sfPlayer[i]));
	}
	for (int i = 0; i < 3; i++) // 쇼군 오른쪽 대기
	{
		__ReleaseSurface(&(g_objEnemy[3].g_sfPlayer[i]));
	}
	for (int i = 0; i < 6; i++) // 쇼군 오른쪽 움직임
	{
		__ReleaseSurface(&(g_objEnemy[4].g_sfPlayer[i]));
	}
	for (int i = 0; i < 4; i++) // 쇼군 공격1 (오른쪽)
	{
		__ReleaseSurface(&(g_objEnemy[5].g_sfPlayer[i]));
	}
	for (int i = 0; i < 5; i++) // 쇼군 공격2 (왼쪽)
	{
		__ReleaseSurface(&(g_objEnemy[6].g_sfPlayer[i]));
	}
	// 쇼군 공격2 이펙트(왼쪽)
	__ReleaseSurface(&(g_objEnemy[7].g_sfPlayer[0]));
	for (int i = 0; i < 5; i++) // 쇼군 공격2 (오른쪽)
	{
		__ReleaseSurface(&(g_objEnemy[8].g_sfPlayer[i]));
	}
	// 쇼군 공격2 이펙트(오른쪽)
	__ReleaseSurface(&(g_objEnemy[9].g_sfPlayer[i]));
	for (int i = 0; i < 3; i++)
	{
		__ReleaseSurface(&(g_objEnemy[10].g_sfPlayer[i]));
	}
	for (int i = 0; i < 3; i++)
	{
		__ReleaseSurface(&(g_objEnemy[11].g_sfPlayer[i]));
	}

	// 수리검
	for (i = 0; i < 4; i++)
	{
		__ReleaseSurface(&(g_objItem[0].g_sfPlayer[i]));
	}
	__ReleaseSurface(&g_sfBG);
	__ReleaseSurface(&g_sfBack);
}

bool bMove = FALSE;
bool bJump = FALSE;
bool bHit = FALSE;
bool bAttack = FALSE;
bool bDJump = FALSE;
bool bSAttack = FALSE;
bool bLiveShuriken = FALSE;

bool bShogunMove = FALSE; 
bool bShogunAttack = FALSE;
bool LeftFace = TRUE;
bool bDragonBlow = FALSE;
bool bEnemyHit = FALSE;

static int jumpHeight = 0;

static int nBgX = 1;
static int InitPlayerXPosition = 50;
static int InitPlayerYPosition = 390;
int TransitionShurikenXPosition = 0;
int TransitionShurikenYPosition = 0;
int PlayerMaxStamina = 100;
int PlayerCurrentStamina = 100;

int InitShogunXPosition = 450;

RECT playerRect = GetSpriteRect(50 + curX, 380, &(g_objPlayer[0].g_sfPlayer[g_objPlayer[0].nAni]));
RECT EnemyRect = GetSpriteRect(InitShogunXPosition + 50, 370, &(g_objEnemy[0].g_sfPlayer[0]));
RECT playerSlashRect = GetSpriteRect(50 + curX + 30, 380, &(g_objPlayer[3].g_sfPlayer[g_objPlayer[0].nAni]));
RECT ShurikenRect = GetSpriteRect(TransitionShurikenXPosition + shurikenX,
	TransitionShurikenYPosition, &(g_objItem[0].g_sfPlayer[g_objPlayer[0].nAni]));

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC dcScreen;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:
		//// 표면 생성 및 기타
		dcScreen = GetDC(hWnd);
		__Init(dcScreen);

		// 플레이어 애니메이션 생성
		__Idle(dcScreen, g_objPlayer);
		__Move(dcScreen, g_objPlayer);
		__Jump(dcScreen, g_objPlayer);
		__Attack(dcScreen, g_objPlayer);
		__ShurikenAttack(dcScreen, g_objPlayer);
		__DJump(dcScreen, g_objPlayer);
		__Shuriken(dcScreen, g_objItem);

		// 쇼군 애니메이션 생성
		__ShogunIdle(dcScreen, g_objEnemy);
		__ShogunMove(dcScreen, g_objEnemy);
		__ShogunAttack1(dcScreen, g_objEnemy);
		__ShogunAttack2(dcScreen, g_objEnemy);
		__ShogunAttack2Effect(dcScreen, g_objEnemy);
		__ShogunHit(dcScreen, g_objEnemy);
		ReleaseDC(hWnd, dcScreen);

		//// 플레이어
		g_objPlayer[0].nAni = 0; // 오른쪽 대기
		g_objPlayer[1].nAni = 0; // 오른쪽 움직임
		g_objPlayer[2].nAni = 0; // 점프
		g_objPlayer[3].nAni = 0; // 오른쪽 공격
		g_objPlayer[4].nAni = 0; // 더블 점프
		g_objPlayer[5].nAni = 0; // 수리검 공격
		g_objPlayer[6].nAni = 0; // 왼쪽 대기
		g_objPlayer[7].nAni = 0; // 왼쪽 움직임
		g_objPlayer[8].nAni = 0; // 왼쪽 공격
		g_objPlayer[9].nAni = 0; // 왼쪽 점프
		g_objPlayer[10].nAni = 0; // 더블 점프
		g_objPlayer[11].nAni = 0; // 

		// 쇼군
		g_objEnemy[0].nAni = 0; // LIdle
		g_objEnemy[1].nAni = 0; // Move
		g_objEnemy[2].nAni = 0; // LAttack1
		g_objEnemy[3].nAni = 0; // RIdle
		g_objEnemy[4].nAni = 0; // RMove
		g_objEnemy[5].nAni = 0; // RAttack1
		g_objEnemy[6].nAni = 0; // LAttack2
		g_objEnemy[7].nAni = 0; // DragonBlow
		g_objEnemy[8].nAni = 0; // DragonBlow
		g_objEnemy[9].nAni = 0; // DragonBlow
		g_objEnemy[10].nAni = 0; // ShogunHit
		g_objEnemy[11].nAni = 0; // ShogunRHit

		// 수리검
		g_objItem[0].nAni = 0;
		g_objItem[1].nAni = 0;
		g_objItem[2].nAni = 0;

		////
		::Sleep(100);

		//// 타이머 생성		
		// 60 FPS ( 1000ms / 60fps = 16.6ms )
		// 정밀도 NT : 10ms ( 100 fps )
		//        98 : 55ms (  18 fps )
		SetTimer(hWnd, ID_TM_MAINLOOP, 16, MainLoopProc);
		SetTimer(hWnd, ID_TM_ANIMATION_PLAYER, 160, NULL);
		SetTimer(hWnd, ID_TM_ANIMATION_ENEMY, 320, NULL);

		return 0;
	case WM_SETFOCUS:
		::OutputDebugString("WM_SETFOCUS");
		return 0;

	case WM_TIMER:
		if (wParam == ID_TM_ANIMATION_PLAYER)
		{

			if (bJump)
			{
				g_objPlayer[11].nAni++;
				if (g_objPlayer[11].nAni >= 2)
				{
					g_objPlayer[11].nAni = 0;
					bJump = FALSE;
				}
			}


			g_objPlayer[11].nAni++;
			if (g_objPlayer[11].nAni >= 2)
			{
				g_objPlayer[11].nAni = 0;
			}


			if (!bMove)
			{
				if (!bJump)
				{
					if (bAttack || bSAttack)
					{
						if (bAttack)
						{
							g_objPlayer[3].nAni++;
							if (g_objPlayer[3].nAni >= 4)
							{
								g_objPlayer[3].nAni = 0;
								bAttack = FALSE;
							}
							g_objPlayer[8].nAni++;
							if (g_objPlayer[8].nAni >= 4)
							{
								g_objPlayer[8].nAni = 0;
								bAttack = FALSE;
							}
						}
						else
						{
							g_objPlayer[5].nAni++;
							if (g_objPlayer[5].nAni >= 3)
							{
								g_objPlayer[5].nAni = 0;
								bSAttack = FALSE;
							}
						}
					}
					else
					{
						g_objPlayer[0].nAni;
						g_objPlayer[6].nAni;
					}
				}
				else
				{
					if (bDJump)
					{
						curY -= (jumpHeight + 50);
						jumpHeight--;
						jumpHeight -= GRAVITY_ACCELERATION;

						g_objPlayer[4].nAni++;
						if (g_objPlayer[4].nAni >= 4)
						{
							g_objPlayer[4].nAni = 0;
							jumpHeight -= 80;
							jumpHeight = 0;
							bDJump = FALSE;
						}
						if (curY >= 330)
						{
							curY = 310;
							bJump = FALSE;
							bDJump = FALSE;
							break;
						}
					}
					else
					{
						curY -= (jumpHeight + 50);
						jumpHeight--;
						jumpHeight -= GRAVITY_ACCELERATION;

						g_objPlayer[2].nAni++;
						if (g_objPlayer[2].nAni >= 1)
						{
							g_objPlayer[2].nAni = 0;
							jumpHeight -= 80;
						}
						if (curY >= 330)
						{
							curY = 310;
							jumpHeight = 0;
							bJump = FALSE;
							break;
						}

						g_objPlayer[9].nAni++;
						if (g_objPlayer[9].nAni >= 1)
						{
							g_objPlayer[9].nAni = 0;
							jumpHeight -= 80;
						}
						if (curY >= 330)
						{
							curY = 310;
							jumpHeight = 0;
							bJump = FALSE;
							break;
						}
					}
				}
			}
			else
			{
				if (RightFace)
				{
					g_objPlayer[1].nAni++;
					if (g_objPlayer[1].nAni >= 3) g_objPlayer[1].nAni = 0;
				}
				else
				{
					g_objPlayer[7].nAni++;
					if (g_objPlayer[7].nAni >= 3) g_objPlayer[7].nAni = 0;
				}
			}

			if (bLiveShuriken) // 수리검이 살아있을 경우
			{

				g_objItem[0].nAni++;
				if (g_objItem[0].nAni >= 4)
				{
					g_objItem[0].nAni = 0;
				}
				shurikenX += 20;
				if (shurikenX == 200)
				{
					shurikenX = 0;
					bLiveShuriken = FALSE;
				}
			}

		}
		if (wParam == ID_TM_ANIMATION_ENEMY)
		{
			if (!bEnemyHit)
			{
				if (!bShogunMove)
				{
					if (bShogunAttack)
					{
						if (bDragonBlow)
						{
							g_objEnemy[6].nAni++;
							if (g_objEnemy[6].nAni >= 5)
							{
								g_objEnemy[6].nAni = 0;
								bDragonBlow = FALSE;
								bShogunAttack = FALSE;
							}
							g_objEnemy[8].nAni++;
							if (g_objEnemy[8].nAni >= 5)
							{
								g_objEnemy[8].nAni = 0;
								bDragonBlow = FALSE;
								bShogunAttack = FALSE;
							}
						}
						else
						{
							if (LeftFace)
							{
								EcurX += 15;
								g_objEnemy[2].nAni++;
								if (g_objEnemy[2].nAni >= 4)
								{
									g_objEnemy[2].nAni = 0;
									bShogunAttack = FALSE;
								}
							}
							else
							{
								EcurX -= 15;
								g_objEnemy[5].nAni++;
								if (g_objEnemy[5].nAni >= 4)
								{
									g_objEnemy[5].nAni = 0;
									bShogunAttack = FALSE;
								}
							}
						}
					}
					else
					{
						g_objEnemy[0].nAni++;
						if (g_objEnemy[0].nAni >= 3)
						{
							g_objEnemy[0].nAni = 0;
						}
						g_objEnemy[3].nAni++;
						if (g_objEnemy[3].nAni >= 3)
						{
							g_objEnemy[3].nAni = 0;
						}
					}
				}
				else
				{
					if (LeftFace)
					{
						EcurX += 5;
						g_objEnemy[1].nAni++;
						if (g_objEnemy[1].nAni >= 6)
						{
							g_objEnemy[1].nAni = 0;
						}
					}
					else
					{
						EcurX -= 5;
						g_objEnemy[4].nAni++;
						if (g_objEnemy[4].nAni >= 6)
						{
							g_objEnemy[4].nAni = 0;
						}
					}
				}
			}
			else
			{
				g_objEnemy[10].nAni++;
				if (g_objEnemy[10].nAni >= 2)
				{
					bEnemyHit = FALSE;
					bShogunMove = FALSE;
					bShogunAttack = FALSE;
					g_objEnemy[10].nAni = 0;
				}

				g_objEnemy[11].nAni++;
				if (g_objEnemy[11].nAni >= 2)
				{
					bEnemyHit = FALSE;
					bShogunMove = FALSE;
					bShogunAttack = FALSE;
					g_objEnemy[11].nAni = 0;
				}
			}
		}
		return 0;

	case WM_DESTROY:
		KillTimer(hWnd, ID_TM_MAINLOOP);
		KillTimer(hWnd, ID_TM_ANIMATION_PLAYER);
		KillTimer(hWnd, ID_TM_ANIMATION_ENEMY);
		__DestroyAll();
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void SlashCheck(HDC hdc)
{
	RECT SlashRect = GetSpriteRect(InitPlayerXPosition + curX,
		380, &(g_objPlayer[3].g_sfPlayer[2]));
	RECT SlashLRect = GetSpriteRect(InitPlayerXPosition + curX,
		380, &(g_objPlayer[8].g_sfPlayer[2]));
	RECT obstacleRect = __DrawHitBox(hdc, g_objEnemy, InitShogunXPosition - EcurX, 350, 0);

	if (CheckCollision(SlashRect, obstacleRect))
	{
		// 충돌 사각형 그리기
		HBRUSH hBrush, hOldBrush;
		RECT intersection;
		if (IntersectRect(&intersection, &SlashRect, &obstacleRect)|| IntersectRect(&intersection,&SlashLRect, &obstacleRect)) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 브러쉬 생성
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			FrameRect(hdc, &intersection, hBrush); // 사각형 그리기
			SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush); // 브러쉬 삭제
			bEnemyHit = TRUE;
		}
	}
}

void ShurikenHitCheck(HDC hdc)
{
	RECT ShurikenRect = GetSpriteRect(TransitionShurikenXPosition + shurikenX, 
		TransitionShurikenYPosition, &(g_objItem[0].g_sfPlayer[g_objPlayer[0].nAni]));
	RECT obstacleRect = __DrawHitBox(hdc, g_objEnemy, InitShogunXPosition - EcurX, 350, 0);

	if (CheckCollision(ShurikenRect, obstacleRect))
	{
		// 충돌 사각형 그리기
		HBRUSH hBrush, hOldBrush;
		RECT intersection;
		if (IntersectRect(&intersection, &ShurikenRect, &obstacleRect)) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 브러쉬 생성
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			FrameRect(hdc, &intersection, hBrush); // 사각형 그리기
			SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush); // 브러쉬 삭제
			bLiveShuriken = FALSE;
			bEnemyHit = TRUE;
			shurikenX = 0;
		}
	}
}

void CALLBACK MainLoopProc(HWND hWnd, UINT, UINT, DWORD)
{
	char  strBuff[24];
	HDC   dcScreen;
	PAINTSTRUCT ps;
	BOOL  bRval, bSval, bTval;
	int i = 0;
	int rndShogunAttack = rand() % 2;

	//// 연산부
	if (curX < -105)
		curX = -105;
	else if (curX > 500)
		curX = 500;

	if (nBgX > 1) nBgX = 1;
	if (nBgX < -770) nBgX = -770;

	if (EcurX > 400)
	{
		LeftFace = FALSE;
	}

	//// 출력부
	dcScreen = GetDC(hWnd);
	{
		// 쇼군 AI
		HBRUSH hBrush, hOldBrush;

		RECT playerRect = GetSpriteRect(50 + curX, 380, &(g_objPlayer[0].g_sfPlayer[g_objPlayer[0].nAni]));
		RECT EnemyLObserveRect = GetSpriteRect((InitShogunXPosition - 150) - EcurX, 330, &(g_objEnemy[0].g_sfPlayer[0]));
		RECT EnemyLAttackRect = GetSpriteRect((InitShogunXPosition - 100) - EcurX, 330, &(g_objEnemy[0].g_sfPlayer[0]));

		RECT EnemyRObserveRect = GetSpriteRect((InitShogunXPosition + 150) - EcurX, 330, &(g_objEnemy[0].g_sfPlayer[0]));
		RECT EnemyRAttackRect = GetSpriteRect((InitShogunXPosition + 100) - EcurX, 330, &(g_objEnemy[0].g_sfPlayer[0]));

		if (CheckCollision(playerRect, EnemyLObserveRect)) // 왼쪽 시야에 있을 때
		{
			if (CheckCollision(playerRect, EnemyLAttackRect))
			{
				if (!bShogunAttack)
				{
					switch (rndShogunAttack)
					{
					case 0:
						g_objEnemy[6].nAni = 0;
						LeftFace = TRUE;
						bShogunMove = FALSE;
						bShogunAttack = TRUE;
						break;
					case 1:
						g_objEnemy[2].nAni = 0;
						LeftFace = TRUE;
						bShogunMove = FALSE;
						bShogunAttack = TRUE;
						bDragonBlow = TRUE;
					}
				}
			}
			else
			{
				if (!bShogunAttack)
				{
					LeftFace = TRUE;
					bShogunMove = TRUE;
					bShogunAttack = FALSE;
				}
			}
		}
		else if (CheckCollision(playerRect, EnemyRObserveRect)) // 오른쪽 시야에 있을 때
		{
			if (CheckCollision(playerRect, EnemyRAttackRect))
			{
				LeftFace = FALSE;
				bShogunMove = FALSE;
				bShogunAttack = TRUE;
			}
			else
			{
				LeftFace = FALSE;
				bShogunMove = TRUE;
				bShogunAttack = FALSE;
			}
		}
		else // 모든 시야에서 벗어났을 때
		{
			bShogunMove = FALSE;
			bShogunAttack = FALSE;
		}

		//// 배경
		__PutImage(g_sfBack.dcSurface, nBgX, 0, &g_sfBG);

		
		
		if (!bMove)
		{
			if (!bJump)
			{
				if (bAttack || bSAttack)
				{
					if (bAttack)
					{
						if (RightFace)
						{
							bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, InitPlayerYPosition,
								&(g_objPlayer[3].g_sfPlayer[g_objPlayer[3].nAni]));
							SlashCheck(dcScreen);

						}
						else
						{
							bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, InitPlayerYPosition,
								&(g_objPlayer[8].g_sfPlayer[g_objPlayer[8].nAni]));
							SlashCheck(dcScreen);
						}
					}
					else
					{
						bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, InitPlayerYPosition,
							&(g_objPlayer[5].g_sfPlayer[g_objPlayer[5].nAni]));
					}
				}
				else
				{
					if (RightFace)
					{

						bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, InitPlayerYPosition,
							&(g_objPlayer[0].g_sfPlayer[0]));
					}
					else
					{
						bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, InitPlayerYPosition,
							&(g_objPlayer[6].g_sfPlayer[0]));
					}
				}
			}
			else
			{
				if (bDJump)
				{
					bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, curY + 20,
						&(g_objPlayer[4].g_sfPlayer[g_objPlayer[4].nAni]));
				}
				else
				{
					if (RightFace)
					{
						bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, curY,
							&(g_objPlayer[2].g_sfPlayer[g_objPlayer[2].nAni]));
					}
					else
					{
						bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, curY,
							&(g_objPlayer[9].g_sfPlayer[g_objPlayer[9].nAni]));
					}
				}
			}
		}
		else
		{
			if (RightFace)
			{
				bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, InitPlayerYPosition,
					&(g_objPlayer[1].g_sfPlayer[g_objPlayer[1].nAni]));
			}
			else
			{
				bRval = __PutSprite(g_sfBack.dcSurface, InitPlayerXPosition + curX, InitPlayerYPosition,
					&(g_objPlayer[7].g_sfPlayer[g_objPlayer[7].nAni]));
			}
		}
		
		if (bLiveShuriken)
		{
			bSval = __PutSprite(g_sfBack.dcSurface, TransitionShurikenXPosition + shurikenX, TransitionShurikenYPosition,
				&(g_objItem[0].g_sfPlayer[g_objItem[0].nAni]));
			ShurikenHitCheck(dcScreen);
		}

		//// 적 애니메이션
		if (!bEnemyHit)
		{
			if (!bShogunMove)
			{
				if (!bShogunAttack)
				{
					if (LeftFace)
					{
						__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 0);
						bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
							&(g_objEnemy[0].g_sfPlayer[g_objEnemy[0].nAni]));

					}
					else
					{
						__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 3);
						bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
							&(g_objEnemy[3].g_sfPlayer[g_objEnemy[3].nAni]));
					}
				}
				else
				{
					if (bDragonBlow)
					{
						if (LeftFace)
						{
							__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 6);
							bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
								&(g_objEnemy[6].g_sfPlayer[g_objEnemy[6].nAni]));

							if (g_objEnemy[6].nAni == 4)
							{
								bSval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX - 100, 390,
									&(g_objEnemy[7].g_sfPlayer[0]));
							}
						}
						else
						{
							__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 8);
							bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
								&(g_objEnemy[8].g_sfPlayer[g_objEnemy[8].nAni]));

							if (g_objEnemy[8].nAni == 4)
							{
								bSval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition + EcurX + 100, 390,
									&(g_objEnemy[9].g_sfPlayer[0]));
							}
						}
					}
					else
					{
						if (LeftFace)
						{
							__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 2);
							bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
								&(g_objEnemy[2].g_sfPlayer[g_objEnemy[2].nAni]));
						}
						else
						{
							__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 5);
							bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
								&(g_objEnemy[5].g_sfPlayer[g_objEnemy[5].nAni]));
						}
					}
				}
			}
			else
			{
				if (LeftFace)
				{
					__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 1);
					bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
						&(g_objEnemy[1].g_sfPlayer[g_objEnemy[1].nAni]));
				}
				else
				{
					__DrawHitBox(dcScreen, g_objEnemy, InitShogunXPosition - EcurX, 350, 1);
					bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
						&(g_objEnemy[4].g_sfPlayer[g_objEnemy[4].nAni]));
				}
			}
		}
		else
		{
			if (LeftFace)
			{
				bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
					&(g_objEnemy[10].g_sfPlayer[g_objEnemy[10].nAni]));
			}
			else
			{
				bRval = __PutSprite(g_sfBack.dcSurface, InitShogunXPosition - EcurX, 350,
					&(g_objEnemy[11].g_sfPlayer[g_objEnemy[11].nAni]));
			}
		}

		bRval = __PutSprite(g_sfBack.dcSurface, 280, 20,
			&(g_objState[0].g_sfPlayer[g_objState[0].nAni]));


		::wsprintf(strBuff, "%d / %d", PlayerCurrentStamina, PlayerMaxStamina);
		::TextOut(g_sfBack.dcSurface, 10, 10, strBuff, strlen(strBuff));

		//// 출력 완료
		__CompleteBlt(dcScreen, &g_sfBack);
	}
	ReleaseDC(hWnd, dcScreen);
}

void __KeyProc(HWND hWnd)
{
	if (GetKeyState(VK_LEFT) & 0x80)
	{
		if (!bJump && !bAttack && !bSAttack)
		{
			RightFace = FALSE;
			bMove = TRUE;
			curX -= 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		if (bDJump)
		{
			curX -= 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}

	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		if (!bJump && !bAttack && !bSAttack)
		{
			RightFace = TRUE;
			bMove = TRUE;
			curX += 2;
			InvalidateRect(hWnd, NULL, TRUE);
			
		}

		if (bDJump)
		{
			curX += 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	else if (!(GetKeyState(VK_LEFT) & 0x80 && !(GetKeyState(VK_RIGHT) & 0x80)))
	{
		bMove = FALSE;
	}

	if (GetKeyState(VK_UP) & 0x80)
	{
		if (!bJump)
		{
			bJump = TRUE;
			jumpHeight = JUMP_HEIGHT;
			curY -= 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}

	if (GetKeyState(VK_DOWN) & 0x80)
	{


		if (PlayerCurrentStamina < 100)
		{
			if (PlayerCurrentStamina > 100)
				PlayerCurrentStamina = 100;
			PlayerCurrentStamina += 2;
		}

	}

	if (GetKeyState(0x5A) & 0x80) // z
	{
		if (!bAttack && !bJump && PlayerCurrentStamina >= 5)
		{
			bAttack = TRUE;
			bMove = FALSE;
			InvalidateRect(hWnd, NULL, TRUE);
			PlayerCurrentStamina -= 5;
		}
	}

	if (GetKeyState(0x58) & 0x80) // x
	{
		if (!bSAttack && PlayerCurrentStamina >= 10)
		{
			TransitionShurikenXPosition = __TransitionShuriken(InitPlayerXPosition + 85, curX);
			TransitionShurikenYPosition = __TransitionShuriken(InitPlayerYPosition + 15, -jumpHeight);
			bSAttack = TRUE;
			bLiveShuriken = TRUE;
			bMove = FALSE;
			InvalidateRect(hWnd, NULL, TRUE);
			PlayerCurrentStamina -= 10;
		}
	}

	if (GetKeyState(0x43) & 0x80) // c
	{
		if (bJump && !bDJump)
		{
			bDJump = TRUE;
			jumpHeight = JUMP_HEIGHT;
			curY -= 2;
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
}

int __TransitionShuriken(int PlayerPosition, int TransitionPlayerPosition)
{
	return PlayerPosition + TransitionPlayerPosition;
}

// 플레이어 외형 변경(?)