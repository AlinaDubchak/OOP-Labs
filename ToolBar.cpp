#include "framework.h"
#include "toolbar.h"
#include "resource.h"
#include "resource1.h"
#include <commctrl.h>

void ToolBar::OnCreate(HWND hWnd, HINSTANCE hInst)
{
    TBBUTTON tbb[6];

    ZeroMemory(tbb, sizeof(tbb)); //обнулення пам'яті.
    tbb[0].iBitmap = 0;
    tbb[0].fsState = TBSTATE_ENABLED;
    tbb[0].fsStyle = TBSTYLE_BUTTON; //тип елементу - кнопка
    tbb[0].idCommand = ID_TOOL_OPEN_FILE; //цей ID буде у повідомленні WM_COMMAND

    tbb[1].iBitmap = 1;
    tbb[1].fsState = TBSTATE_ENABLED;
    tbb[1].fsStyle = TBSTYLE_BUTTON;
    tbb[1].idCommand = ID_TOOL_SAVE_FILE;

    tbb[2].iBitmap = 2;
    tbb[2].fsState = TBSTATE_ENABLED;
    tbb[2].fsStyle = TBSTYLE_BUTTON;
    tbb[2].idCommand = ID_TOOL_MOVE;

    tbb[3].iBitmap = 3;
    tbb[3].fsState = TBSTATE_ENABLED;
    tbb[3].fsStyle = TBSTYLE_BUTTON;
    tbb[3].idCommand = ID_TOOL_BRIGHTNESS;

    tbb[4].iBitmap = 4;
    tbb[4].fsState = TBSTATE_ENABLED;
    tbb[4].fsStyle = TBSTYLE_BUTTON;
    tbb[4].idCommand = ID_TOOL_CONTRAST;

    tbb[5].iBitmap = 5;
    tbb[5].fsState = TBSTATE_ENABLED;
    tbb[5].fsStyle = TBSTYLE_BUTTON;
    tbb[5].idCommand = ID_TOOL_RGB;


    SendMessage(hwndToolBar, TB_ADDBUTTONS, 6, (LPARAM)&tbb);

    hwndToolBar = CreateToolbarEx(hWnd, //батьківське вікно
        WS_CHILD | WS_VISIBLE | WS_BORDER | WS_CLIPSIBLINGS | CCS_TOP |
        TBSTYLE_TOOLTIPS,
        IDC_MY_TOOLBAR, //ID дочірнього вікна Toolbar
        6, //кількість зображень у BITMAP
        hInst,
        IDB_BITMAP1, //ID ресурсу BITMAP
        tbb,
        6, //кількість кнопок (разом з роздільником)
        24, 24, 24, 24, //розміри кнопок та зображень BITMAP
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
//---обробник повідомлення WM_SIZE---
void ToolBar::OnSize(HWND hWnd)
{
    RECT rc, rw;
    if (hwndToolBar)
    {
        GetClientRect(hWnd, &rc); //нові розміри головного вікна
        GetWindowRect(hwndToolBar, &rw); //нам потрібно знати висоту Toolbar
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
        case ID_TOOL_OPEN_FILE:
            lstrcpy(lpttt->szText, L"Відкрити файл");
            break;
        case ID_TOOL_SAVE_FILE:
            lstrcpy(lpttt->szText, L"Зберегти файл");
            break;
        case ID_TOOL_MOVE:
            lstrcpy(lpttt->szText, L"Переміститися");
            break;
        case ID_TOOL_BRIGHTNESS:
            lstrcpy(lpttt->szText, L"Яскравість");
            break;
        case ID_TOOL_CONTRAST:
            lstrcpy(lpttt->szText, L"Контраст");
            break;
        case ID_TOOL_RGB:
            lstrcpy(lpttt->szText, L"RGB канали");
            break;
        default: lstrcpy(lpttt->szText, L"Щось невідоме");
        }
    }
}
