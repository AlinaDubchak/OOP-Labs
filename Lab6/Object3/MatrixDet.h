#pragma once
#include "framework.h"


class MatrixDet
{
private:
	MatrixDet() {}
	MatrixDet(const MatrixDet& root);
	MatrixDet& operator = (const MatrixDet&);

	double det = 0;
	int Num = 0;
	std::string matrixText = "";
	int** matrix = 0;
public:
	static MatrixDet& getInstance()
	{
		static MatrixDet instance;
		return instance;
	}

	void OnCreate(HWND);

	int takeClipboard(HWND, long);
	int** takeMatrix(std::string);
	void takeSubMtrx(int**, int**, int, int, int);
	int takeDeterminant(int**, int);
	void OnPaint(HWND, HDC);
};