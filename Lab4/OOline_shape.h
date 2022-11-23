#pragma once

class LineOOShape : public LineShape, public EllipseShape
{
public:
	virtual void Show(HDC);
	virtual void DrawTrace(HDC, int, int, int, int);
	virtual Shape* New();

};

