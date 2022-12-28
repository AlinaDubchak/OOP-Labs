#include "framework.h"
#include "Scrollbar_Settings.h"
#include "Brightness_Settings.h"
#include "Contrast_Settings.h"
#include "RGB_Settings.h"
#include <vector>// реалізує динамічний масив


class Viewer
{
private:
	HWND		hWnd;
	HINSTANCE	hInst;
	HDC			hdc;
	Scrollbar	scrollbar; //для приватного використання поля в load file
	
	char* img_name; 
	const int STARTY = 37;
	const int STARTX = 0;
	int IsOpenedFile;
	int img_width;
	int img_height;
	int scrollX;
	int scrollY;

	int x1;
	int y1;
	int x2;
	int y2;
	float zoom;

	BYTE* pixelMatrix;	
	BITMAPINFO MyBMInfo; //определяет информацию о размерах и цвете для растрового формата DIB
public:
	Viewer();
	void resetScreen();
	BYTE* getPixArray(HBITMAP hBitmap);
	BYTE* saveFile(int* img_w, int* img_h);
	void Paint(HWND hwnd, HINSTANCE hinst);
	void setFile(char* name);
	void loadFile(HDC hdc);
	void zoomHDC();
	void unzoomHDC();
	void setScrollX(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void setScrollY(HWND hWnd, WPARAM wParam, LPARAM lParam);
	void brightnessChange();
	void contrastChange();
	void rgbChange();
};