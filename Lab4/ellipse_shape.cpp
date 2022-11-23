#include "framework.h"
#include "Shape.h"
#include "ellipse_shape.h"
#include "resource.h"

EllipseShape::~EllipseShape() {}

Shape* EllipseShape::New()
{
	return new EllipseShape;
}

void EllipseShape::Show(HDC hdc)
{
	HBRUSH hBrush, hBrushOld;
	colorfill = RGB(0, 112, 255);
	hBrush = (HBRUSH)CreateSolidBrush(colorfill);
	hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, xs1, ys1, xs2, ys2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	
}

void EllipseShape::DrawTrace(HDC hdc, int x1, int x2, int y1, int y2)
{
	Ellipse(hdc, x1, y1, x2, y2);
}

