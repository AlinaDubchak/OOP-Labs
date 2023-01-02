#pragma once
#include "framework.h"

using namespace std;

class MatrixDialog
{
private:
	MatrixDialog() {}
	MatrixDialog(const MatrixDialog& root);
	MatrixDialog& operator = (const MatrixDialog&);
public:
	static MatrixDialog& getInstance()
	{
		static MatrixDialog instance;
		return instance;
	}

	static wstring GetBoxText(HWND, int);
	static void SendCopyData(HWND, HWND, void*, long);

	void StartWnd(HINSTANCE, HWND);
	void EndWnd();
};