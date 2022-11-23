#pragma once

class EllipseShape : public virtual Shape
{
public:
	virtual ~EllipseShape();
	virtual void Show(HDC);
	virtual void DrawTrace(HDC, int, int, int, int);
	virtual Shape* New();

};
