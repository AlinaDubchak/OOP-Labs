#include "framework.h"
#include "Shape.h"
#include "line_shape.h"
#include "resource.h"

LineShape::~LineShape() {}

Shape* LineShape::New()
{
	return new LineShape;
}

void LineShape::Show(HDC hdc)
{
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
}

void LineShape::DrawTrace(HDC hdc, int x1, int x2, int y1, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

