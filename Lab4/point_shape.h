#pragma once

class PointShape : public virtual Shape
{
public:
	virtual ~PointShape();
	virtual void Show(HDC);
	virtual void DrawTrace(HDC, int, int, int, int);
	virtual Shape* New();

};
