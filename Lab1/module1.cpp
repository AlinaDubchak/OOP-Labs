#include "framework.h"
#include "module1.rh"



static WCHAR* ptext;
static INT_PTR CALLBACK Work1(HWND hDlg, UINT message, WPARAM wParam,
	LPARAM lParam)
{
	static int pos, nxMin, nxMax;
	static HWND hwndScroll;
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		nxMin = 0;
		nxMax = 100;
		pos = 50;
		SetScrollRange(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, nxMin, nxMax,
			TRUE);
		SetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, pos, TRUE);
		return (INT_PTR)TRUE;
	case WM_HSCROLL:
		pos = GetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL);
		SetDlgItemInt(hDlg, IDC_STATIC5, pos, FALSE);
		switch (LOWORD(wParam))
		{
		case SB_LINELEFT:
			pos--;
			break;
		case SB_LINERIGHT:
			pos++;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			pos = HIWORD(wParam);
			break;
		default: break;
		}
		SetScrollPos(GetDlgItem(hDlg, IDC_SCROLLBAR1), SB_CTL, pos, TRUE);

		break;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int res = GetDlgItemInt(hDlg, IDC_STATIC5, NULL, FALSE);
			_itow_s(res, ptext, 48, 10);
			EndDialog(hDlg, 1);
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

int Func_MOD1(HWND hWnd, HINSTANCE hI, WCHAR* p) {

	ptext = p;
	return DialogBox(hI, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, Work1);
}