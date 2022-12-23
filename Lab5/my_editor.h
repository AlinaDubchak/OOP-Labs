#pragma once
#include "pch.h"
#include "Resource.h"
#include "shape.h"
#include "editor.h"
#include <string>


#define MY_SHAPE_ARRAY_SIZE		105

class MyEditor : public Editor
{
private:
	MyEditor() {}
	MyEditor(const MyEditor&);
	MyEditor& operator=(MyEditor&);
	Shape** pcshape = new Shape * [MY_SHAPE_ARRAY_SIZE];
	HWND handler;
    long x1, y1, x2, y2;
public:
	static MyEditor& getInstance()
	{
		static MyEditor instance;
		return instance;
	}
	void Start(Shape*);
	void RemoveShape(int);
	void UpdateWindow();
	std::string GetDetails();
	void OnLMBDown(HWND);
	void OnLMBUp(HWND);
	void OnMouseMove(HWND);
	void OnPaint(HWND, int);
	void OnInitMenuPopup(HWND, WPARAM);
	~MyEditor();
	
};