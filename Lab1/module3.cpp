#include "framework.h"
#include "module3.rh"

INT_PTR CALLBACK Work3(HWND hDlg, UINT message, WPARAM wParam, LPARAM
	lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BACK11)
		{
			EndDialog(hDlg, 1);
			return (INT_PTR)TRUE;
		}
		if (LOWORD(wParam) == IDCANCEL || LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, 0);
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
int Func_MOD3(HWND hWnd, HINSTANCE hI) {
	return DialogBox(hI, MAKEINTRESOURCE(IDD_DIALOG11), hWnd, Work3);
}
