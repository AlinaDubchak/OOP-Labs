#include "Contrast.h"

static int pos;
static int nMinPos = 0;
static int nMaxPos = 200;
static const int defaultN = 100;
static HWND hWndScrollBar_MOD2;

static INT_PTR CALLBACK Contrast_MOD(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);

static void OnLineLeft(HWND hDlg);
static void OnLineRight(HWND hDlg);
static void OnClose(HWND hDlg);

static void OnThumbPosAndTrack(HWND hDlg, WPARAM wParam);

int WindowContrast(HINSTANCE hInst, HWND hWnd, int* i)
{
    int res = DialogBox(hInst, MAKEINTRESOURCE(IDD_WORK_MOD2), hWnd, Contrast_MOD);
    if (pos != defaultN) { *i = (pos - defaultN) * 2; }
    else { *i = 0; }
    return res;
}

INT_PTR CALLBACK Contrast_MOD(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    switch (iMessage)
    {
    case WM_INITDIALOG:
        hWndScrollBar_MOD2 = GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD2);
        pos = defaultN;
        SetScrollRange(hWndScrollBar_MOD2, SB_CTL, nMinPos, nMaxPos, TRUE);
        SetScrollPos(hWndScrollBar_MOD2, SB_CTL, pos, TRUE);
        SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos-defaultN, TRUE);
        break;
    case WM_HSCROLL:
        pos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1_MOD2), SB_CTL);
        switch (LOWORD(wParam))
        {
        case SB_LINELEFT:
            OnLineLeft(hDlg);
            break;
        case SB_LINERIGHT:
            OnLineRight(hDlg);
            break;
        case SB_THUMBPOSITION:
        case SB_THUMBTRACK:
            OnThumbPosAndTrack(hDlg, wParam);
            break;
        default: break;
        }
        SetScrollPos(hWndScrollBar_MOD2, SB_CTL, pos, TRUE);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case IDOK:
            EndDialog(hDlg, 1);
            return (INT_PTR)TRUE;
            break;
        case IDCANCEL:
            OnClose(hDlg);
            return (INT_PTR)TRUE;
            break;
        }
        break;
    case WM_CLOSE:
    {
        OnClose(hDlg);
    }
    break;
    default: break;
    }
    return FALSE;
}

void OnLineLeft(HWND hDlg)
{
    if (pos != nMinPos)
    {
        pos--;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos - defaultN, TRUE);
}

void OnLineRight(HWND hDlg)
{
    if (pos != nMaxPos)
    {
        pos++;
    }
    SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos - defaultN, TRUE);
}


void OnThumbPosAndTrack(HWND hDlg, WPARAM wParam)
{
    pos = HIWORD(wParam);
    SetDlgItemInt(hDlg, IDC_STATIC_MOD2, pos - defaultN, TRUE);
}


void OnClose(HWND hDlg)
{
    pos = defaultN;
    EndDialog(hDlg, 0);
}
