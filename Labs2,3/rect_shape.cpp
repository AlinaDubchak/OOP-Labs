#include "framework.h"
#include "rect_shape.h"


void RectShape:: Show(HDC hdc) {
	HBRUSH hBrush, hBrushOld;
	colorfill = RGB(255,255,51);
	hBrush = (HBRUSH)CreateSolidBrush(colorfill);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	

	Rectangle(hdc, xs1, ys1, xs2, ys2);
	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
};
