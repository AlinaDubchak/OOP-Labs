#pragma once


class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
	long colorfill;
public:
	virtual ~Shape();
	void Set(long x1, long y1, long x2, long y2);
	virtual void Show(HDC) = 0;
	virtual void DrawTrace(HDC, int, int, int, int) = 0;
	virtual Shape* New() = 0;
};
