#include "MatrixDet.h"

using namespace std;

void MatrixDet::OnCreate(HWND hWnd)
{
	takeClipboard(hWnd, 10009);
	matrix = takeMatrix(matrixText);
	det = takeDeterminant(matrix, Num);

	InvalidateRect(hWnd, NULL, TRUE);
}

void MatrixDet::OnPaint(HWND hWnd, HDC hdc)
{
	using convert_type = std::codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;

	string sDet;
	wstring wsDet;

	stringstream ss;
	ss << std::fixed << std::setprecision(0) << det;
	ss >> sDet;
	wsDet = converter.from_bytes(sDet);

	TextOut(hdc, 50, 50, (LPCWSTR)wsDet.c_str(), (int)wcslen((LPCWSTR)wsDet.c_str()));
}