#include "framework.h"
#include "Shape.h"
#include "line_shape.h"
#include "rect_shape.h"
#include "cube_shape.h"
#include "resource.h"


Shape* CubeShape::New()
{
	return new CubeShape;
}

void CubeShape::DrawTrace(HDC hdc, int x1, int x2, int y1, int y2)
{
	RectShape::DrawTrace(hdc, x1, x2, y1, y2);

	LineShape::DrawTrace(hdc, x1, x1 - 30, y1, y1 + 30);
	LineShape::DrawTrace(hdc, x2, x2 - 30, y2, y2 + 30);
	LineShape::DrawTrace(hdc, x1, x1 - 30, y2, y2 + 30);
	LineShape::DrawTrace(hdc, x2, x2 - 30, y1, y1 + 30);
	LineShape::DrawTrace(hdc, x1 - 30, x2 - 30, y1 + 30, y1 + 30);
	LineShape::DrawTrace(hdc, x2 - 30, x2 - 30, y1 + 30, y2 + 30);
	LineShape::DrawTrace(hdc, x2 - 30, x1 - 30, y2 + 30, y2 + 30);
	LineShape::DrawTrace(hdc, x1 - 30, x1 - 30, y2 + 30, y1 + 30);

	xs1 = x1; xs2 = x2; ys1 = y1; ys2 = y2;
}

void CubeShape::Show(HDC hdc)
{
	long x1, y1, x2, y2;
	RectShape::Show(hdc);

	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;

	LineShape::Set(x1, y1, x1 - 30, y1 + 30);
	LineShape::Show(hdc);
	LineShape::Set(x2, y2, x2 - 30, y2 + 30);
	LineShape::Show(hdc);
	LineShape::Set(x1, y2, x1 - 30, y2 + 30);
	LineShape::Show(hdc);
	LineShape::Set(x2, y1, x2 - 30, y1 + 30);
	LineShape::Show(hdc);
	LineShape::Set(x1 - 30, y1 + 30, x2 - 30, y1 + 30);
	LineShape::Show(hdc);
	LineShape::Set(x2 - 30, y1 + 30, x2 - 30, y2 + 30);
	LineShape::Show(hdc);
	LineShape::Set(x2 - 30, y2 + 30, x1 - 30, y2 + 30);
	LineShape::Show(hdc);
	LineShape::Set(x1 - 30, y2 + 30, x1 - 30, y1 + 30);
	LineShape::Show(hdc);

	xs1 = x1; xs2 = x2; ys1 = y1; ys2 = y2;

}

