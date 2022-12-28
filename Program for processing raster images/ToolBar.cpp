#include "toolbar.h"


void ToolBar::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[TOOLS+1];
    ZeroMemory(tbb, sizeof(tbb));
    for (int i = 0; i < TOOLS; i++) {
        tbb[i].iBitmap = i;
        tbb[i].fsState = TBSTATE_ENABLED;
        tbb[i].fsStyle = TBSTYLE_BUTTON;
        tbb[i].idCommand = tools[i];
    }

    tbb[TOOLS].iBitmap = TOOLS;
    tbb[TOOLS].fsState = TBSTATE_ENABLED;
    tbb[TOOLS].fsStyle = TBSTYLE_SEP;
    tbb[TOOLS].idCommand = 0;

    hwndToolBar = CreateToolbarEx(hWnd,
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP | TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        TOOLS,
        hInst,
        IDB_BITMAP1,
        tbb,
        TOOLS+1,
        24, 24, 24, 24,
        sizeof(TBBUTTON));
}

void ToolBar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc);
        GetWindowRect(hwndToolBar, &rw);
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}

void ToolBar::PressBtn(HWND hWnd, LPARAM lParam)
{
 if (oldlParam)
 {
 SendMessage(hwndToolBar, TB_PRESSBUTTON, oldlParam, 0);
 }
 SendMessage(hwndToolBar, TB_PRESSBUTTON, lParam, 1);
 oldlParam = lParam;
}


void ToolBar::OnToolOpenFile(Viewer *view)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_OPENFILE, 1);
    files.OpenFile(view);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_OPENFILE, 0);
}

void ToolBar::OnToolSaveFile(Viewer *view)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_SAVEFILE, 1);
    files.SaveFile(view);
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_SAVEFILE, 0);
}

void ToolBar::OnToolZoom(Viewer *view)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ZOOM, 1);
    view->zoomHDC(); // на указатель view викликаЇмо функц≥ю zoom
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_ZOOM, 0);
}

void ToolBar::OnToolUnzoom(Viewer* view)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_UNZOOM, 1);
    view->unzoomHDC();
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_UNZOOM, 0);
}

void ToolBar::OnToolBrightness(Viewer* view)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_BRIGHTNESS, 1);
    view->brightnessChange();
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_BRIGHTNESS, 0);
}

void ToolBar::OnToolContrast(Viewer* view)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_CONTRAST, 1);
    view->contrastChange();
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_CONTRAST, 0);
}

void ToolBar::OnToolRGB(Viewer* view)
{
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RGB, 1);
    view->rgbChange();
    SendMessage(hwndToolBar, TB_PRESSBUTTON, ID_TOOL_RGB, 0);
}


void ToolBar::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_OPENFILE:
            lstrcpy(lpttt->szText, "Open file");
            break;
        case ID_TOOL_SAVEFILE:
            lstrcpy(lpttt->szText, "Save file");
            break;
        case ID_TOOL_ZOOM:
            lstrcpy(lpttt->szText, "Zoom");
            break;
        case ID_TOOL_UNZOOM:
            lstrcpy(lpttt->szText, "Unzoom");
            break;
        case ID_TOOL_BRIGHTNESS:
            lstrcpy(lpttt->szText, "Brightness");
            break;
        case ID_TOOL_CONTRAST:
            lstrcpy(lpttt->szText, "Contrast");
            break;
        case ID_TOOL_RGB:
            lstrcpy(lpttt->szText, "RGB chanels");
            break;
        default: lstrcpy(lpttt->szText, "ўось нев≥доме");
        }
    }
}
