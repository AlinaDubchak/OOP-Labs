#include "viewer.h"
#include <fstream>


Viewer::Viewer() { //���������� ���������
	hWnd = NULL;
	hInst = NULL;
	IsOpenedFile = 0;
	zoom = 1;
	scrollX = 0;
	scrollY = 0;
	pixelMatrix = new BYTE[1]; //type BYTE but like unsigned char
}

void Viewer::resetScreen() { // ����������� ����
	InvalidateRect(hWnd, NULL, TRUE);
}

void Viewer::setFile(char* name) { //������������ ���� ��������
	img_name = name;
	IsOpenedFile = 1;
	resetScreen();
}

void Viewer::loadFile(HDC hdc) {                                                             //�������� ��� bitmap image
	BITMAP          bitmap;                                                                    //������������ ��� ������ � �������������, ������������� ������� ��������.
	HDC             hdcMem;
	HBITMAP			oldBitmap;                                                                // ��������� �������� ��'���� �������
	HBITMAP			hBitmap;
	hBitmap = (HBITMAP)LoadImage(NULL, img_name, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	pixelMatrix = getPixArray(hBitmap);
	hdcMem = CreateCompatibleDC(hdc);                                                                       // �������� ����������� ��������
	oldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);                                                    // �������������� ��� ���� bitmap

	GetObject(hBitmap, sizeof(BITMAP), &bitmap);                                                             //��������� ���������� ��� ��������� ������������ �������

	img_width = bitmap.bmWidth;                                                                               //width bitmap
	img_height = bitmap.bmHeight;                                                                             // height bitmap
	 
	BitBlt(hdc, STARTX, STARTY, STARTX + img_width, STARTY + img_height, hdcMem, 0, 0, SRCCOPY);                 //��������� �������� ������� ������ ������ � �����, ��������������� �������������� �������� ��
	                                                                                             //��������� ��������� ��������� ���������� � ������� �������� ����������
	SelectObject(hdcMem, oldBitmap);                                                              // ����������� ����� ������ ���������
	DeleteDC(hdcMem);                                                                             // �������� ��������, ��� ��� �� �����
	DeleteObject(hBitmap);

	scrollbar.OnNewBmp(hWnd, img_width, img_height);
}

BYTE* Viewer::saveFile(int* img_w, int* img_h) { //���������� ������ ����� �� ������� ������ ���
	*img_w = img_width;
	*img_h = img_height;
	return pixelMatrix;
}

void Viewer::Paint(HWND hwnd, HINSTANCE hinst) //����������� �������� � ��������� ���
{
	if (hWnd == NULL) {
		hWnd = hwnd;
		hInst = hinst;
	}

	PAINTSTRUCT		ps;
	
	hdc = BeginPaint(hWnd, &ps);

	if (IsOpenedFile == 1) {
		loadFile(hdc);
		IsOpenedFile = 0;
	}
	else {
		StretchDIBits(hdc, STARTX - scrollX, STARTY - scrollY, img_width * zoom, img_height * zoom, 0, 0, img_width, img_height, pixelMatrix, &MyBMInfo, DIB_RGB_COLORS, SRCCOPY); //�������� ������ � ����� ��� �������������� ��������
		                                                                                                                                                        //� ���������-����������� ��������� ������� (DIB) � �������� ������������� ���������.
	}

	EndPaint(hWnd, &ps);
}

BYTE* Viewer::getPixArray(HBITMAP hBitmap)
{
	HDC hdc, hdcMem;

	hdc = GetDC(NULL);
	hdcMem = CreateCompatibleDC(hdc);                                                                                                  //������� �������� ���������� � ������

	MyBMInfo = { 0 };
	MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);

	if (0 == GetDIBits(hdcMem, hBitmap, 0, 0, NULL, &MyBMInfo, DIB_RGB_COLORS))                                                         //��������� ���� ��������� ������������ ��������� ������� � �������� �� � ����� ��� DIB, ��������� �������� ������.
	{
		MessageBox(hWnd, "ERROR", "Error", IDOK);
	}

	BYTE* lpPixels = new BYTE[MyBMInfo.bmiHeader.biSizeImage];

	MyBMInfo.bmiHeader.biSize = sizeof(MyBMInfo.bmiHeader);
	MyBMInfo.bmiHeader.biBitCount = 24;
	MyBMInfo.bmiHeader.biCompression = BI_RGB;
	MyBMInfo.bmiHeader.biHeight = (MyBMInfo.bmiHeader.biHeight < 0) ? (-MyBMInfo.bmiHeader.biHeight) : (MyBMInfo.bmiHeader.biHeight);

	if (0 == GetDIBits(hdc, hBitmap, 0, MyBMInfo.bmiHeader.biHeight, (LPVOID)lpPixels, &MyBMInfo, DIB_RGB_COLORS))
	{
		MessageBox(hWnd, "ERROR", "Error", IDOK);
	}

	return lpPixels;
}

void Viewer::zoomHDC()
{
	zoom += 0.2f;
	resetScreen();
}

void Viewer::unzoomHDC()
{
	zoom = zoom <= 1 ? 1 : zoom - 0.2f;
	resetScreen();
}

void Viewer::setScrollX(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	scrollX = scrollbar.OnHorizontalScroll(hWnd, wParam, lParam);
	resetScreen();
}

void Viewer::setScrollY(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
	scrollY = scrollbar.OnVerticalScroll(hWnd, wParam, lParam);
	resetScreen();
}



void Viewer::brightnessChange()
{
	int counter = 0;
	double R, G, B;
	int brightness;
	Func_MOD1(hInst, hWnd, &brightness);

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {

			R = pixelMatrix[counter+2] + brightness;
			G = pixelMatrix[counter+1] + brightness;
			B = pixelMatrix[counter] + brightness;

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter + 2] = (BYTE)R;
			pixelMatrix[counter + 1] = (BYTE)G;
			pixelMatrix[counter] = (BYTE)B;
			
			counter+=4;
		}
	}

	resetScreen();
}

void Viewer::contrastChange()
{
	int counter = 0;
	double R, G, B;
	int contrast;
	Func_MOD2(hInst, hWnd, &contrast);
	double factor = (259.0 * (contrast + 255.0)) / (255.0 * (259.0 - contrast));
	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {

			R = (factor * (pixelMatrix[counter+2] - 128) + 128);
			G = (factor * (pixelMatrix[counter+1] - 128) + 128);
			B = (factor * (pixelMatrix[counter] - 128) + 128);

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter + 2] = (BYTE)R;
			pixelMatrix[counter + 1] = (BYTE)G;
			pixelMatrix[counter] = (BYTE)B;

			counter += 4;
		}
	}
	resetScreen();
}

void Viewer::rgbChange()
{
	int counter = 0;
	double R, G, B;
	int rMultiplier, gMultiplier, bMultiplier;
	Func_MOD3(hInst, hWnd, &rMultiplier, &gMultiplier, &bMultiplier);

	for (int y = 0; y < img_height; y++) {
		for (int x = 0; x < img_width; x++) {

			R = pixelMatrix[counter + 2] + rMultiplier;
			G = pixelMatrix[counter + 1] + gMultiplier;
			B = pixelMatrix[counter] + bMultiplier;

			if (R < 0) R = 0;
			if (R > 255) R = 255;
			if (G < 0) G = 0;
			if (G > 255) G = 255;
			if (B < 0) B = 0;
			if (B > 255) B = 255;

			pixelMatrix[counter + 2] = (BYTE)R;
			pixelMatrix[counter + 1] = (BYTE)G;
			pixelMatrix[counter] = (BYTE)B;

			counter += 4;
		}
	}

	resetScreen();
}