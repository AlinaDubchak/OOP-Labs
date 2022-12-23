#include "pch.h"
#include "my_table.h"

static LPCSTR exceptionString = "Can't open a file";
static LPCSTR filePath = "table.txt";

static HWND _Hwnd;
static HWND mainWinHandler;

int CurListSel;


BOOL CALLBACK Table(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;
        break;
    case WM_COMMAND:
        if (LOWORD(wParam) == IDCANCEL)
        {
            ShowWindow(_Hwnd, SW_HIDE); //приховати таблицю
            return TRUE;
        }
        if (LOWORD(wParam) == IDC_EXIT)
        {
            ShowWindow(_Hwnd, SW_HIDE); //кнопка виходу з вікна таблиці
            return TRUE;
        }
        if (HIWORD(wParam) == LBN_SELCHANGE) {  //обраний елемент
            CurListSel = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, 0, 0);
            InvalidateRect(mainWinHandler, NULL, TRUE);
        }
        if (HIWORD(wParam) == LBN_DBLCLK) {  //вилучення елементу з таблиці
            CurListSel = SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_GETCURSEL, 0, 0);
            if (CurListSel != 0) {
                SendMessage(GetDlgItem(hWnd, IDC_LIST), LB_DELETESTRING, CurListSel, 0);
            }
        }
        break;
    }
    return (INT_PTR)FALSE;
}


void MyTable::CreateTable(HINSTANCE hInst, HWND hWnd) {  //створення немодального вікна
    mainWinHandler = hWnd;
	tableHwnd = CreateDialog(hInst, MAKEINTRESOURCE(IDD_TABLE), 0, Table);
    _Hwnd = tableHwnd;
	ShowWindow(tableHwnd, SW_SHOW);
}

void MyTable::ClearTableFile() { //очищення минулих координат з текстового файлу
	FILE* fout;
	fopen_s(&fout, filePath, "wt");
	if (fout)
	{
		fprintf(fout, "");
		fclose(fout);
	}
}

void MyTable::Add(std::string shapeDetails)
{
	std::ofstream myTableFile; //запис в поток

	myTableFile.open(filePath, std::ofstream::app);

	if (myTableFile.is_open())   // запис у текстовий файл координат
	{
		myTableFile << shapeDetails << std::endl;
	}
	else throw new std::exception(exceptionString);

	myTableFile.close();


	SendDlgItemMessage(tableHwnd, IDC_LIST, LB_ADDSTRING, //відлбраження координат у вікні таблиці
		0, (LPARAM)shapeDetails.c_str());
}