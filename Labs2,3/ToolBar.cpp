#include "framework.h"
#include "toolbar.h"
#include "resource.h"
#include "resource1.h"
#include <commctrl.h>

void ToolBar::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[4];

    ZeroMemory(tbb, sizeof(tbb));
    tbb[0].iBitmap = 0;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON;
    tbb[0].idCommand = ID_TOOL_DOT;

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_LINE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_RECT;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_ELLIPSE;

    SendMessage(hwndToolBar, TB_ADDBUTTONS, 4, (LPARAM)&tbb);

    hwndToolBar = CreateToolbarEx(hWnd, //���������� ����
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP|
        TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR,
        4, //������� ��������� � BITMAP
        hInst,
        IDB_BITMAP1, //ID ������� BITMAP
        tbb,
        4, //������� ������ (����� � �����������)
        24, 24, 24, 24, //������ ������ �� ��������� BITMAP
        sizeof(TBBUTTON));
};
void ToolBar::PressBtn(HWND hWnd, LPARAM lParam)
{
    if (oldlParam)
    {
        SendMessage(hwndToolBar, TB_PRESSBUTTON, oldlParam, 0);
    }
    SendMessage(hwndToolBar, TB_PRESSBUTTON, lParam, 1);
    oldlParam = lParam;
}
//---�������� ����������� WM_SIZE---
void ToolBar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); //��� ������ ��������� ����
        GetWindowRect(hwndToolBar, &rw); //��� ������� ����� ������ Toolbar
        MoveWindow(hwndToolBar, 0, 0, rc.right - rc.left, rw.bottom - rw.top, FALSE);
    }
}
void ToolBar::OnNotify(HWND hWnd, WPARAM wParam, LPARAM lParam)
{
    LPNMHDR pnmh = (LPNMHDR)lParam;
    if (pnmh->code == TTN_NEEDTEXT)
    {
        LPTOOLTIPTEXT lpttt = (LPTOOLTIPTEXT)lParam;
        switch (lpttt->hdr.idFrom)
        {
        case ID_TOOL_DOT:
            lstrcpy(lpttt->szText, L"������");
            break;
        case ID_TOOL_LINE:
            lstrcpy(lpttt->szText, L"˳���");
            break;
        case ID_TOOL_RECT:
            lstrcpy(lpttt->szText, L"�����������");
            break;
        case ID_TOOL_ELLIPSE:
            lstrcpy(lpttt->szText, L"����");
            break;
        default: lstrcpy(lpttt->szText, L"���� �������");
        }
    }
}


