#pragma once
#include "Shape.h"

#define MY_SHAPE_ARRAY_SIZE 105

class MyEditor
{
private:
	Shape** pcshape;
	Shape* thisShape;
	int j = 0;
	bool LBdown = false;
	int xstart, xend, ystart, yend;
public:
	MyEditor(void);
	~MyEditor();
	void Start(Shape*);
	void OnLBdown(HWND);
	void OnLBup(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND);
};
