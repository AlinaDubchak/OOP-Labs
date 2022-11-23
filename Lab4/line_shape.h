#pragma once

class LineShape : public virtual Shape
{
public:
	virtual ~LineShape();
	virtual void Show(HDC);
	virtual void DrawTrace(HDC, int, int, int, int);
	virtual Shape* New();

};
