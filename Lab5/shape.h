#include "pch.h"
#include "colors.h"
#include "toolbar.h"
#include <string>

class Shape
{
protected:
	long xs1, ys1, xs2, ys2;
	long colorfill;
public:
	void Set(long x1, long y1, long x2, long y2);
	int* GetCoords();
	virtual void Show(HDC, int) = 0;
	virtual void DrawTrace(HDC) = 0;
	virtual int InitMenuPopup() = 0;
	virtual Shape* New() = 0;
	virtual std::string GetName() = 0;
	~Shape();
};

class PointShape : public Shape
{
public:
	virtual void Show(HDC, int);
	void DrawTrace(HDC);
	int InitMenuPopup();
	virtual Shape* New();
	virtual std::string GetName();
};

class LineShape : public virtual Shape
{
public:
	virtual void Show(HDC, int);
	void DrawTrace(HDC);
	int InitMenuPopup();
	virtual Shape* New();
	virtual std::string GetName();
};

class RectangleShape : public virtual Shape
{
public:
	virtual void Show(HDC, int);
	void DrawTrace(HDC);
	int InitMenuPopup();
	virtual Shape* New();
	virtual std::string GetName();
};

class EllipseShape : public virtual Shape
{
public:
	virtual void Show(HDC, int);
	void DrawTrace(HDC);
	int InitMenuPopup();
	virtual Shape* New();
	virtual std::string GetName();
};

class CubeShape : public RectangleShape, public LineShape
{
public:
	void Show(HDC, int);
	void DrawTrace(HDC);
	int InitMenuPopup();
	virtual Shape* New();
	virtual std::string GetName();
};

class LineOOShape : public LineShape, public EllipseShape
{
public:
	void Show(HDC, int);
	void DrawTrace(HDC);
	int InitMenuPopup();
	virtual Shape* New();
	virtual std::string GetName();
};