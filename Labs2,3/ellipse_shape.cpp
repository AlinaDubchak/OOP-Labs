#include "framework.h"
#include "ellipse_shape.h"


void EllipseShape::Show(HDC hdc) {

	long xStart = xs2 - (2 * (xs2 - xs1)); //до правого верхнього кута
	long yStart = ys2 - (2 * (ys2 - ys1));
	
	Ellipse(hdc, xStart, yStart, xs2, ys2);
	
}