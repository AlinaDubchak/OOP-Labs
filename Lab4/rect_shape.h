#pragma once

class RectShape : public virtual Shape
{
public:
	virtual ~RectShape();
	virtual void Show(HDC);
	virtual void DrawTrace(HDC, int, int, int, int);
	virtual Shape* New();

};
