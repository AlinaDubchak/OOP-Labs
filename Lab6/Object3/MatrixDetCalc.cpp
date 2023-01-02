#include "MatrixDet.h"

using namespace std;

int MatrixDet:: GetFromClipboard(HWND hWnd, long maxsize) // Для читання вмісту Clipboard 
{
	HGLOBAL hglobal;
	LPTSTR lptstr;
	long size, result;
	result = 0;
	char* dest = new char[maxsize];
	if (!IsClipboardFormatAvailable(CF_TEXT)) return 0;
	if (!OpenClipboard(hWnd)) return 0;
	hglobal = GetClipboardData(CF_TEXT);
	if (hglobal != NULL)
	{
		lptstr = (LPTSTR)GlobalLock(hglobal);
		if (lptstr != NULL)
		{
			size = (long)strlen((char*)lptstr);
			if (size > maxsize)
			{
				lptstr[maxsize] = 0;
				size = (long)strlen((char*)lptstr);
			}
			result = size;
			strcpy_s(dest, maxsize, (char*)lptstr);
			GlobalUnlock(hglobal);
		}
	}
	CloseClipboard();

	return result;
}

int** MatrixDet::takeMatrix(std::string text)
{
	stringstream stream(text);

	int size = (int)std::count(text.cbegin(), text.cend(), '\n');
	Num = size;
	int** result = new int* [size];
	for (int i = 0; i < size; i++)
		result[i] = new int[size];

	int element;
	int i = 0;
	int j = 0;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			stream >> element;
			result[i][j] = element;
		}
	}

	return result;
}

void MatrixDet::CalcSubMatrix(int** src, int** dest, int Num, int row, int column)
{
	int dp = 0;
	int db = 0;

	int size = Num - 1;
	for (int p = 0; p < size; p++)
	{
		if (p == row) dp = 1;

		db = 0;
		for (int b = 0; b < size; b++)
		{
			if (b == column) db = 1;
			dest[p][b] = src[p + dp][b + db];
		}
	}
}

int MatrixDet::CalcDetMatrix(int** matrix, int size)
{
	int deter = 0;
	int degr = 1;

	if (size == 1)
		return matrix[0][0];

	if (size == 2)
		return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];

	int** tmp = new int* [size - 1];
	for (int i = 0; i < size - 1; i++)
		tmp[i] = new int[size - 1];

	for (int j = 0; j < size; j++)
	{
		CalcSubMatrix(matrix, tmp, size, 0, j);
		deter = deter + (degr * matrix[0][j] * CalcDetMatrix(tmp, size - 1));
		degr = -degr;
	}

	for (int i = 0; i < size - 1; i++)
		delete[] tmp[i];
	delete[] tmp;

	return deter;
}

