#ifndef __GRAPHICENGINE_H__
#define __GRAPHICENGINE_H__

#include <windows.h>

typedef struct SURFACEINFOtag
{
	HDC			dcSurface;		// 비트맵이 적재되있는 표면 DC
	HBITMAP		hBmp;			// 비트맵 핸들
	HBITMAP		hOldBmp;		// 이전 비트맵 핸들 ( dc 해제시 참조 )
	int			nWidth;
	int			nHeight;
	COLORREF	crColorKey;		// 컬러키
} SURFACEINFO;

typedef struct OBJ_MONtag
{
	SURFACEINFO	g_sfPlayer[16];
	int			nAni;
	int			nLife;
	int			nStepX;
	int			nStepY;
} OBJ_MON;

//// dcScreen와 호환되는 후면표면DC 생성
BOOL __CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo);

//// 표면 생성 및 로드
//// 각종 오브젝트 또는 비트맵 DC 생성 및 비트맵 로드
void __LoadSurface(HDC dcScreen, SURFACEINFO* psInfo);

//// 생성된 표면 해제
void __ReleaseSurface(SURFACEINFO* psInfo);

//// 이미지 출력
BOOL __PutImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo);

//// 이미지 블렌드
BOOL __PutImageBlend(HDC dcDst, int x, int y, SURFACEINFO* psInfo, int nAlpha);

//// 스프라이트
BOOL __PutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo);

//// dcScreen에 표면을 복사 ( 후면표면 -> 화면DC )
BOOL __CompleteBlt(HDC dcScreen, SURFACEINFO* psInfo);

//// DIB -> DDB로 변환
HBITMAP __MakeDDBFromDIB(HDC hdc, char* Path);

//// SURFACEINFO 이미지 초기화
void __SetImgSurface(SURFACEINFO* psfInfo);

//// SURFACEINFO 스프라이트 초기화
void __SetSprSurface(SURFACEINFO* psfInfo, COLORREF crColorKey);

#endif