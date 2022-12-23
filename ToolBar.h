#pragma once
#pragma comment(lib, "comctl32.lib")

class ToolBar {
protected:
	HWND hwndToolBar = NULL;
	LPARAM oldlParam = NULL;
public:
	void OnCreate(HWND, HINSTANCE);
	void OnSize(HWND);
	void PressBtn(HWND, LPARAM);
	void OnNotify(HWND, WPARAM, LPARAM);
	void OnToolOpenFile();
	void OnToolSaveFile();
	void OnToolZoom();
	void OnToolUnzoom();
	void OnToolHand();
	void OnToolBrightness();
	void OnToolContrast();
	void OnToolRGB();
};