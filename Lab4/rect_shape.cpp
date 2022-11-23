#include "framework.h"
#include "Shape.h"
#include "rect_shape.h"
#include "resource.h"

RectShape::~RectShape() {}

Shape* RectShape::New()
{
	return new RectShape;
}


void RectShape::Show(HDC hdc)
{
	Rectangle(hdc, xs1, ys1, xs2, ys2);
}

void RectShape::DrawTrace(HDC hdc, int x1, int x2, int y1, int y2)
{
	Rectangle(hdc, x1, y1, x2, y2);
}

