#ifndef __GRAPHICENGINE_H__
#define __GRAPHICENGINE_H__

#include <windows.h>

typedef struct SURFACEINFOtag
{
	HDC			dcSurface;		// ��Ʈ���� ������ִ� ǥ�� DC
	HBITMAP		hBmp;			// ��Ʈ�� �ڵ�
	HBITMAP		hOldBmp;		// ���� ��Ʈ�� �ڵ� ( dc ������ ���� )
	int			nWidth;
	int			nHeight;
	COLORREF	crColorKey;		// �÷�Ű
} SURFACEINFO;

typedef struct OBJ_MONtag
{
	SURFACEINFO	g_sfPlayer[16];
	int			nAni;
	int			nLife;
	int			nStepX;
	int			nStepY;
} OBJ_MON;

//// dcScreen�� ȣȯ�Ǵ� �ĸ�ǥ��DC ����
BOOL __CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo);

//// ǥ�� ���� �� �ε�
//// ���� ������Ʈ �Ǵ� ��Ʈ�� DC ���� �� ��Ʈ�� �ε�
void __LoadSurface(HDC dcScreen, SURFACEINFO* psInfo);

//// ������ ǥ�� ����
void __ReleaseSurface(SURFACEINFO* psInfo);

//// �̹��� ���
BOOL __PutImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo);

//// �̹��� ����
BOOL __PutImageBlend(HDC dcDst, int x, int y, SURFACEINFO* psInfo, int nAlpha);

//// ��������Ʈ
BOOL __PutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo);

//// dcScreen�� ǥ���� ���� ( �ĸ�ǥ�� -> ȭ��DC )
BOOL __CompleteBlt(HDC dcScreen, SURFACEINFO* psInfo);

//// DIB -> DDB�� ��ȯ
HBITMAP __MakeDDBFromDIB(HDC hdc, char* Path);

//// SURFACEINFO �̹��� �ʱ�ȭ
void __SetImgSurface(SURFACEINFO* psfInfo);

//// SURFACEINFO ��������Ʈ �ʱ�ȭ
void __SetSprSurface(SURFACEINFO* psfInfo, COLORREF crColorKey);

#endif