#pragma once

class CubeShape : public LineShape, public RectShape
{
public:
	virtual void Show(HDC);
	virtual void DrawTrace(HDC, int, int, int, int);
	virtual Shape* New();

};
