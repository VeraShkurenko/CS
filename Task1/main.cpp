#include <tchar.h>
#include "resource.h"
#include <iostream>
#include <fstream>
using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE h, HINSTANCE p, LPTSTR l, int s)
{
    return DialogBox(h, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_INITDIALOG:
        CheckRadioButton(hWnd, IDC_RADIO_TEXT, IDC_RADIO_BINARY, IDC_RADIO_TEXT);
        return TRUE;
    case WM_COMMAND:
        if (wParam == IDC_BUTTON_SAVE)
        {
            TCHAR buf[1024];
            GetDlgItemText(hWnd, IDC_EDIT1, buf, 1024);
#ifdef UNICODE
            wstring ws(buf);
            string str(ws.begin(), ws.end());
#else
            string str = buf;
#endif
            if (IsDlgButtonChecked(hWnd, IDC_RADIO_TEXT) == BST_CHECKED)
            {
                ofstream f("output.txt");
                f << str;
                f.close();
            }
            else
            {
                ofstream f("output.bin", ios::binary);
                f.write(str.c_str(), str.size());
                f.close();
            }
        }
        else if (wParam == IDC_BUTTON_EXIT)
        {
            EndDialog(hWnd, 0);
        }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        return TRUE;
    }
    return FALSE;
}
