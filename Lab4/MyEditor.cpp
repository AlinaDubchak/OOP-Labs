#include "framework.h"
#include "MyEditor.h"

MyEditor::MyEditor(void)
{
	pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE];
}

MyEditor::~MyEditor()
{
	delete[] pcshape;
}

void MyEditor::Start(Shape* shape)
{
	thisShape = shape;
}

void MyEditor::OnLBdown(HWND hWnd)
{
	LBdown = true;
	POINT pt;
	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xstart = xend = pt.x;
	ystart = yend = pt.y;

}

void MyEditor::OnLBup(HWND hWnd)
{
	if (MY_SHAPE_ARRAY_SIZE == j) j = 0;
	if (thisShape)
	{
		pcshape[j] = thisShape;
		pcshape[j]->Set(xstart, ystart, xend, yend);
		thisShape = thisShape->New();
		j++;
	}
	InvalidateRect(hWnd, NULL, TRUE);
	LBdown = false;
}

void MyEditor::OnMouseMove(HWND hWnd)
{
	if (!LBdown) return;
	POINT pt;
	HPEN hPenOld, hPen;
	HDC hdc;
	hdc = GetDC(hWnd);
	SetROP2(hdc, R2_NOTXORPEN);
	hPen = CreatePen(PS_DOT, 1, RGB(0, 0, 254));
	hPenOld = (HPEN)SelectObject(hdc, hPen);

	if (thisShape) thisShape->DrawTrace(hdc, xstart, xend, ystart, yend);

	GetCursorPos(&pt);
	ScreenToClient(hWnd, &pt);
	xend = pt.x;
	yend = pt.y;

	if (thisShape) thisShape->DrawTrace(hdc, xstart, xend, ystart, yend);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	ReleaseDC(hWnd, hdc);
}

void MyEditor::OnPaint(HWND hWnd)
{
	PAINTSTRUCT ps;
	HDC hdc;

	hdc = BeginPaint(hWnd, &ps);
	for (int i = 0; i < j; i++)
	{
		pcshape[i]->Show(hdc);
	}
	EndPaint(hWnd, &ps);
}

