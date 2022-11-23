#include "framework.h"
#include "shape.h"
#include "line_shape.h"
#include "ellipse_shape.h"
#include "OOline_shape.h"
#include "resource.h"


Shape* LineOOShape::New()
{
	return new LineOOShape;
}

void LineOOShape::DrawTrace(HDC hdc, int x1, int x2, int y1, int y2)
{

	LineShape::DrawTrace(hdc, x1, x2, y1, y2);
	EllipseShape::DrawTrace(hdc, x1 - 20, x1 + 20, y1 - 20, y1 + 20);
	EllipseShape::DrawTrace(hdc, x2 + 20, x2 - 20, y2 + 20, y2 - 20);

	xs1 = x1; xs2 = x2; ys1 = y1; ys2 = y2;
}

void LineOOShape::Show(HDC hdc)
{

	long x1, y1, x2, y2;

	LineShape::Show(hdc);

	x1 = xs1; y1 = ys1; x2 = xs2; y2 = ys2;


	EllipseShape::Set(x1 - 20, y1 - 20, x1 + 20, y1 + 20);
	EllipseShape::Show(hdc);
	EllipseShape::Set(x2 + 20, y2 + 20, x2 - 20, y2 - 20);
	EllipseShape::Show(hdc);

	xs1 = x1; xs2 = x2; ys1 = y1; ys2 = y2;

}



