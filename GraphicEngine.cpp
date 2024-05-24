#include "GraphicEngine.h"

BOOL __CreateBackBuffer(HDC dcScreen, int nWidth, int nHeight, int nBPP, SURFACEINFO* psInfo)
{
	psInfo->dcSurface = CreateCompatibleDC(dcScreen);
	psInfo->hBmp = CreateCompatibleBitmap(dcScreen, nWidth, nHeight);
	psInfo->hOldBmp = (HBITMAP)SelectObject(psInfo->dcSurface, psInfo->hBmp);
	PatBlt(psInfo->dcSurface, 0, 0, nWidth, nHeight, PATCOPY);
	psInfo->nWidth = nWidth;
	psInfo->nHeight = nHeight;

	return TRUE;
}

void __LoadSurface(HDC dcScreen, SURFACEINFO* psInfo)
{
	BITMAP  bit;

	psInfo->dcSurface = CreateCompatibleDC(dcScreen);
	psInfo->hOldBmp = (HBITMAP)SelectObject(psInfo->dcSurface, psInfo->hBmp);

	GetObject(psInfo->hBmp, sizeof(BITMAP), &bit);
	psInfo->nWidth = bit.bmWidth;
	psInfo->nHeight = bit.bmHeight;
}

void __ReleaseSurface(SURFACEINFO* psInfo)
{
	SelectObject(psInfo->dcSurface, psInfo->hOldBmp);
	DeleteDC(psInfo->dcSurface);
	DeleteObject(psInfo->hBmp);
}

BOOL __PutImage(HDC dcDst, int x, int y, SURFACEINFO* psInfo)
{
	return BitBlt(dcDst, x, y, psInfo->nWidth, psInfo->nHeight, psInfo->dcSurface, 0, 0, SRCCOPY);
}

BOOL __PutImageBlend(HDC dcDst, int x, int y, SURFACEINFO* psInfo, int nAlpha)
{
	BLENDFUNCTION bf;

	//// BLENDFUNCTION 초기화
	bf.BlendOp = AC_SRC_OVER;	//
	bf.BlendFlags = 0;				//			
	bf.AlphaFormat = 0;				//
	bf.SourceConstantAlpha = nAlpha; // 0 - 255

	//// 알파 블렌드
	return 	AlphaBlend(dcDst,
		x, y, psInfo->nWidth, psInfo->nHeight,
		psInfo->dcSurface,
		0, 0, psInfo->nWidth, psInfo->nHeight,
		bf);
}

BOOL __PutSprite(HDC dcDst, int x, int y, SURFACEINFO* psInfo)
{
	return TransparentBlt(dcDst,
		x, y, psInfo->nWidth, psInfo->nHeight,
		psInfo->dcSurface,
		0, 0, psInfo->nWidth, psInfo->nHeight,
		psInfo->crColorKey);
}

BOOL __CompleteBlt(HDC dcScreen, SURFACEINFO* psInfo)
{
	BitBlt(dcScreen, 0, 0, psInfo->nWidth, psInfo->nHeight, psInfo->dcSurface, 0, 0, SRCCOPY);
	return TRUE;
}

HBITMAP __MakeDDBFromDIB(HDC hdc, char* Path)
{
	HANDLE  hFile;
	DWORD   FileSize, dwRead;
	HBITMAP hBit;
	BITMAPFILEHEADER* fh;
	BITMAPINFO* ih;
	BITMAPINFOHEADER* iheader;
	LPBYTE			 lpMemBlock;

	//// 파일을 연다
	hFile = CreateFile(Path, GENERIC_READ, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		return NULL;
	}

	FileSize = GetFileSize(hFile, NULL);

	lpMemBlock = (LPBYTE)malloc(FileSize);
	fh = (BITMAPFILEHEADER*)lpMemBlock;
	ReadFile(hFile, lpMemBlock, FileSize, &dwRead, NULL);
	CloseHandle(hFile);

	ih = (BITMAPINFO*)(lpMemBlock + sizeof(BITMAPFILEHEADER));
	iheader = (BITMAPINFOHEADER*)(lpMemBlock + sizeof(BITMAPFILEHEADER));

	//// DDB로 변환한다.
	hBit = CreateDIBitmap(hdc,						// hdc
		iheader,					// BITMAPINFOHEADER 헤더
		CBM_INIT,					// 0 또는 CBM_INIT ( 초기화 )
		lpMemBlock + fh->bfOffBits,	// 래스터 어드래스
		ih,							// BITMAPINFO 헤더
		DIB_RGB_COLORS);

	free(lpMemBlock);

	return hBit;
}

void __SetImgSurface(SURFACEINFO* psfInfo)
{
	::memset(psfInfo, 0, sizeof(SURFACEINFO));
}

void __SetSprSurface(SURFACEINFO* psfInfo, COLORREF crColorKey)
{
	::memset(psfInfo, 0, sizeof(SURFACEINFO));
	psfInfo->crColorKey = crColorKey;
}
