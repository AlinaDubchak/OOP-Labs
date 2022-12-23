#include "shape.h"


void Shape::Set(long Sx1, long Sy1, long Sx2, long Sy2)
{
	xs1 = Sx1;
	ys1 = Sy1;
	xs2 = Sx2;
	ys2 = Sy2;
}

int* Shape::GetCoords()
{
	int arr[4] = { xs1, ys1, xs2, ys2 };
	return arr;
}

void PointShape::Show(HDC hdc, int defPen)
{
	COLORREF curColor = defPen == 1 ? black : purple;
	SetPixel(hdc, xs1, ys1, curColor);
	SetPixel(hdc, xs1 - 2, ys1, curColor);
	SetPixel(hdc, xs1 - 1, ys1, curColor);
	SetPixel(hdc, xs1 + 1, ys1, curColor);
	SetPixel(hdc, xs1 + 2, ys1, curColor);
	SetPixel(hdc, xs1, ys1 - 2, curColor);
	SetPixel(hdc, xs1, ys1 - 1, curColor);
	SetPixel(hdc, xs1, ys1 + 1, curColor);
	SetPixel(hdc, xs1, ys1 + 2, curColor);
	SetPixel(hdc, xs1 - 1, ys1 - 1, curColor);
	SetPixel(hdc, xs1 + 1, ys1 - 1, curColor);
	SetPixel(hdc, xs1 - 1, ys1 + 1, curColor);
	SetPixel(hdc, xs1 + 1, ys1 + 1, curColor);
}

void PointShape::DrawTrace(HDC hdc) {}

int PointShape::InitMenuPopup()
{
	return ID_TOOL_POINT;
}

Shape* PointShape::New()
{
	return new PointShape();
}

std::string PointShape::GetName()
{
	return (std::string)"Point";
}

void LineShape::Show(HDC hdc, int defPen)
{
	HPEN hPen, hPenOld;
	COLORREF curColor = defPen == 1 ? black : purple;
	hPen = CreatePen(PS_SOLID, 1, curColor);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void LineShape::DrawTrace(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, blue);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs2, ys2);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int LineShape::InitMenuPopup()
{
	return ID_TOOL_LINE;
}

Shape* LineShape::New()
{
	return new LineShape();
}

std::string LineShape::GetName()
{
	return (std::string)"Line";
}


void RectangleShape::Show(HDC hdc, int defPen)
{
	HPEN hPen, hPenOld;
	HBRUSH hBrush, hBrushOld;

	COLORREF curColor = defPen == 1 ? black : purple;
	hPen = CreatePen(PS_SOLID, 1, curColor);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	hBrush = CreateSolidBrush(NULL_BRUSH);
	hBrushOld = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

	Rectangle(hdc, xs1, ys1, xs2, ys2);

	SelectObject(hdc, hBrushOld);
	DeleteObject(hBrush);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

void RectangleShape::DrawTrace(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, blue);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	LineTo(hdc, xs1, ys2);
	LineTo(hdc, xs2, ys2);
	LineTo(hdc, xs2, ys1);
	LineTo(hdc, xs1, ys1);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int RectangleShape::InitMenuPopup()
{
	return ID_TOOL_RECTANGLE;
}

Shape* RectangleShape::New()
{
	return new RectangleShape();
}

std::string RectangleShape::GetName()
{
	return (std::string)"Rect";
}

void EllipseShape::Show(HDC hdc, int defPen)
{
	HPEN hPen, hPenOld;

	colorfill = RGB(0, 112, 255);
	COLORREF curColor = defPen == 1 ? black : purple;

	HBRUSH hBrush = (HBRUSH)CreateSolidBrush(colorfill);
	HBRUSH hBrushOld = (HBRUSH)SelectObject(hdc, hBrush);

	hPen = CreatePen(PS_SOLID, 1, curColor);
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	Ellipse(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2);

	SelectObject(hdc, hBrushOld);
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	DeleteObject(hBrush);
};

void EllipseShape::DrawTrace(HDC hdc)
{
	HPEN hPen, hPenOld;
	hPen = CreatePen(PS_DOT, 1, blue);
	hPenOld = (HPEN)SelectObject(hdc, hPen);
	MoveToEx(hdc, xs1, ys1, NULL);
	Arc(hdc, 2 * xs1 - xs2, 2 * ys1 - ys2, xs2, ys2, 0, 0, 0, 0);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
}

int EllipseShape::InitMenuPopup()
{
	return ID_TOOL_ELLIPSE;
}

Shape* EllipseShape::New()
{
	return new EllipseShape();
}

std::string EllipseShape::GetName()
{
	return (std::string)"Ellipse";
}

void LineOOShape::Show(HDC hdc, int defPen)
{
	int x1 = xs1, y1 = ys1, x2 = xs2, y2 = ys2;

	LineShape::Set(x1, y1, x2, y2);
	LineShape::Show(hdc, defPen);
	EllipseShape::Set(x1, y1, x1 - 20, y1 - 20);
	EllipseShape::Show(hdc, defPen);
	EllipseShape::Set(x2, y2, x2 - 20, y2 - 20);
	EllipseShape::Show(hdc, defPen);
	LineShape::Set(x1, y1, x2, y2);
}

void LineOOShape::DrawTrace(HDC hdc)
{
	int x1 = xs1, y1 = ys1, x2 = xs2, y2 = ys2;

	LineShape::Set(x1, y1, x2, y2);
	LineShape::DrawTrace(hdc);
	EllipseShape::Set(x1, y1, x1 - 20, y1 - 20);
	EllipseShape::DrawTrace(hdc);
	EllipseShape::Set(x2, y2, x2 - 20, y2 - 20);
	EllipseShape::DrawTrace(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

int LineOOShape::InitMenuPopup()
{
	return ID_TOOL_LINEOO;
}

Shape* LineOOShape::New()
{
	return new LineOOShape();
}

std::string LineOOShape::GetName()
{
	return (std::string)"LineOO";
}

void CubeShape::Show(HDC hdc, int defPen)
{
	int x1 = xs1, y1 = ys1, x2 = xs2, y2 = ys2;
	RectangleShape::Set(x1 - 50, y1 - 50, x1 + 50, y1 + 50);
	RectangleShape::Show(hdc, defPen);
	RectangleShape::Set(x2 - 50, y2 - 50, x2 + 50, y2 + 50);
	RectangleShape::Show(hdc, defPen);
	LineShape::Set(x1 - 50, y1 - 50, x2 - 50, y2 - 50);
	LineShape::Show(hdc, defPen);
	LineShape::Set(x1 - 50, y1 + 50, x2 - 50, y2 + 50);
	LineShape::Show(hdc, defPen);
	LineShape::Set(x1 + 50, y1 + 50, x2 + 50, y2 + 50);
	LineShape::Show(hdc, defPen);
	LineShape::Set(x1 + 50, y1 - 50, x2 + 50, y2 - 50);
	LineShape::Show(hdc, defPen);
	LineShape::Set(x1, y1, x2, y2);
}

void CubeShape::DrawTrace(HDC hdc)
{
	int x1 = xs1, y1 = ys1, x2 = xs2, y2 = ys2;
	RectangleShape::Set(x1 - 50, y1 - 50,
		x1 + 50, y1 + 50);
	RectangleShape::DrawTrace(hdc);
	RectangleShape::Set(x2 - 50, y2 - 50,
		x2 + 50, y2 + 50);
	RectangleShape::DrawTrace(hdc);
	LineShape::Set(x1 - 50, y1 - 50,
		x2 - 50, y2 - 50);
	LineShape::DrawTrace(hdc);
	LineShape::Set(x1 - 50, y1 + 50,
		x2 - 50, y2 + 50);
	LineShape::DrawTrace(hdc);
	LineShape::Set(x1 + 50, y1 + 50,
		x2 + 50, y2 + 50);
	LineShape::DrawTrace(hdc);
	LineShape::Set(x1 + 50, y1 - 50,
		x2 + 50, y2 - 50);
	LineShape::DrawTrace(hdc);
	LineShape::Set(x1, y1, x2, y2);
}

int CubeShape::InitMenuPopup()
{
	return ID_TOOL_CUBE;
}

Shape* CubeShape::New()
{
	return new CubeShape();
}

std::string CubeShape::GetName()
{
	return (std::string)"Cube";
}

Shape::~Shape() {};
