#pragma once
#include "framework.h"
#include "toolbar_resource.h"
#include "files.h"

class ToolBar
{
private:
	Files files;
	HWND hwndToolBar = NULL;
	LPARAM oldlParam = NULL;

	int tools[TOOLS] = {	ID_TOOL_OPENFILE , ID_TOOL_SAVEFILE, ID_TOOL_ZOOM, ID_TOOL_UNZOOM,
							 ID_TOOL_BRIGHTNESS, ID_TOOL_CONTRAST, ID_TOOL_RGB };
public:
	void OnSize(HWND hWnd);
	void PressBtn(HWND, LPARAM);
	void OnCreate(HWND hWnd, HINSTANCE hInst);
	void OnNotify(HWND, WPARAM, LPARAM);
	void OnToolOpenFile(Viewer *view);
	void OnToolSaveFile(Viewer* view);
	void OnToolZoom(Viewer* view);
	void OnToolUnzoom(Viewer* view);
	void OnToolBrightness(Viewer* view);
	void OnToolContrast(Viewer* view);
	void OnToolRGB(Viewer* view);
};