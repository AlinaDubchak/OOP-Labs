#include "CreateMatrix.h"

using namespace std;

int CreateMatrix::PutToClipboard(HWND hWnd, const char* src)
{
	HGLOBAL hglbCopy;
	BYTE* pTmp;
	long len;

	if (src == NULL) return 0;
	if (src[0] == 0) return 0;

	len = (long)strlen(src);
	hglbCopy = GlobalAlloc(GHND, len + 1);

	if (hglbCopy == NULL) return 0;

	pTmp = (BYTE*)GlobalLock(hglbCopy);
	memcpy(pTmp, src, len + 1);
	GlobalUnlock(hglbCopy);

	if (!OpenClipboard(hWnd))
	{
		GlobalFree(hglbCopy);
		return 0;
	}

	EmptyClipboard();
	SetClipboardData(CF_TEXT, hglbCopy); // програма записала дані у Clipboard
	CloseClipboard();

	return 1;
}
void CreateMatrix::OnPaint(HWND hWnd, HDC hdc)
{
	using convert_type = codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;

	string sElem;
	wstring wsElem;
	double elem;

	int x = 10;
	int y = 10;
	for (int i = 0; i < Num; i++)
	{
		for (int j = 0; j < Num; j++)
		{
			stringstream ss;
			elem = matrix[i][j];
			ss << elem;
			ss >> sElem;
			wsElem = converter.from_bytes(sElem);
			TextOut(hdc, x, y, (LPCWSTR)wsElem.c_str(), (int)wcslen((LPCWSTR)wsElem.c_str()));

			x += 50;
		}
		x = 10;
		y += 35;
	}
}
int** CreateMatrix::ConstructMtrx(int size, int minimum, int maximum)
{
	int** result = new int* [size];
	for (int i = 0; i < size; i++)
		result[i] = new int[size];

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dist(minimum, maximum);

	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			result[i][j] = dist(gen);

	return result;
}

void CreateMatrix::OnCopyData(HWND hWnd, WPARAM wParam, LPARAM lParam) // прийом параметрів 
{
	COPYDATASTRUCT* cds;
	cds = (COPYDATASTRUCT*)lParam;
	int* data = (int*)cds->lpData;
	Num = data[0];
	min = data[1];
	max = data[2];

	matrix = ConstructMtrx(Num, min, max);
	matrixText = MatrixStr(matrix, Num);

	PutToClipboard(hWnd, matrixText.c_str());

	InvalidateRect(hWnd, NULL, TRUE);
}

string CreateMatrix::MatrixStr(int** matrixSrc, int size)
{
	using convert_type = codecvt_utf8<wchar_t>;
	wstring_convert<convert_type, wchar_t> converter;

	string result;
	ostringstream stream;
	int element;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			element = matrixSrc[i][j];
			stream << element;
		}
		stream;
	}
	result = stream.str();

	return result;
}