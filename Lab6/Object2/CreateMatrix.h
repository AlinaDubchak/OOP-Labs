#pragma once
#include "framework.h"

using namespace std;

class CreateMatrix
{
private:
	CreateMatrix() {}
	CreateMatrix(const CreateMatrix& root);
	CreateMatrix& operator=(const CreateMatrix&);

	int Num = 0;
	int min = 0;
	int max = 0;

	int** matrix = 0;
	string matrixText = "";
public:
	static CreateMatrix& getInstance()
	{
		static CreateMatrix instance;
		return instance;
	}

	void OnCopyData(HWND, WPARAM, LPARAM);
	void OnPaint(HWND, HDC);
	int** ConstructMtrx(int, int, int);
	string MatrixStr(int**, int);
	int PutToClipboard(HWND, const char*);
};