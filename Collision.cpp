#include "Collision.h"

BOOL CheckCollision(RECT rect1, RECT rect2)
{
	RECT result;
	return IntersectRect(&result, &rect1, &rect2);
}

void HandleCollision(HDC hdc, RECT rect1, RECT rect2)
{
	if (CheckCollision(rect1, rect2))
	{
		// 충돌 사각형 그리기
		HBRUSH hBrush, hOldBrush;
		RECT intersection;
		if (IntersectRect(&intersection, &rect1, &rect2)) {
			hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 브러쉬 생성
			hOldBrush = (HBRUSH)SelectObject(hdc, hBrush);

			FrameRect(hdc, &intersection, hBrush); // 사각형 그리기
			SelectObject(hdc, hOldBrush);
			DeleteObject(hBrush); // 브러쉬 삭제
		}
	}
}

RECT GetSpriteRect(int x, int y, SURFACEINFO* psInfo)
{
	RECT rect;
	rect.left = x;
	rect.top = y;
	rect.right = x + psInfo->nWidth;
	rect.bottom = y + psInfo->nHeight;
	return rect;
}

RECT __DrawHitBox(HDC dcScreen, OBJ_MON* g_obj, int x, int y, int spriteNum)
{
	RECT HitBox;
	HBRUSH hBrush, hOldBrush;
	HitBox = GetSpriteRect(x, 330, &(g_obj[spriteNum].g_sfPlayer[0]));
	hBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색 브러쉬 생성
	hOldBrush = (HBRUSH)SelectObject(dcScreen, hBrush);

	FrameRect(dcScreen, &HitBox, hBrush); // 사각형 그리기
	SelectObject(dcScreen, hOldBrush);
	DeleteObject(hBrush); // 브러쉬 삭제
	return HitBox;
}