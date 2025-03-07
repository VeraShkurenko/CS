#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

CRITICAL_SECTION cs;
HWND hFrom, hTo, hCopy, hStart;
int amount = 0;

DWORD WINAPI WriteToFiles(LPVOID lp)
{
    int lengthInput = SendMessage(hFrom, WM_GETTEXTLENGTH, 0, 0);
    TCHAR* bufferInput = new TCHAR[lengthInput + 1];
    GetWindowText(hFrom, bufferInput, lengthInput + 1);

    TCHAR buf[30];

    EnterCriticalSection(&cs);
    for (int i = 0; i < amount; i++)
    {
        ifstream in(bufferInput);
        wsprintf(buf, TEXT("source_copy_%d.txt"), i);
        ofstream out(buf);

        out << in.rdbuf(); //copy

        in.close();
        out.close();
    }
    LeaveCriticalSection(&cs);

    return 0;
}

DWORD WINAPI ReadFromFiles(LPVOID lp)
{
    int lengthOutput = SendMessage(hTo, WM_GETTEXTLENGTH, 0, 0);
    TCHAR* bufferOutput = new TCHAR[lengthOutput + 1];
    GetWindowText(hTo, bufferOutput, lengthOutput + 1);

    TCHAR buf[30];

    EnterCriticalSection(&cs);
    for (int i = 0; i < amount; i++)
    {
        wsprintf(buf, TEXT("source_copy_%d.txt"), i);
        ifstream in(buf);
        ofstream out(bufferOutput, ios::app);

        out << in.rdbuf() << endl;

        in.close();
        out.close();
    }
    LeaveCriticalSection(&cs);

    return 0;
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hFrom = GetDlgItem(hWnd, IDC_EDIT1);
        hTo = GetDlgItem(hWnd, IDC_EDIT2);
        hCopy = GetDlgItem(hWnd, IDC_EDIT3);
        hStart = GetDlgItem(hWnd, IDC_BUTTON1);
        SetWindowText(hFrom, TEXT("source.txt"));
        SetWindowText(hTo, TEXT("result.txt"));

        InitializeCriticalSection(&cs);

        return TRUE;
    case WM_COMMAND:
        if (wParam == IDC_BUTTON1)
        {
            int length = SendMessage(hCopy, WM_GETTEXTLENGTH, 0, 0);
            TCHAR* buffer = new TCHAR[length + 1];
            GetWindowText(hCopy, buffer, length + 1);
            amount = stoi(buffer);

            HANDLE hThread = CreateThread(NULL, 0, WriteToFiles, 0, 0, NULL);
            CloseHandle(hThread);
            hThread = CreateThread(NULL, 0, ReadFromFiles, 0, 0, NULL);
            CloseHandle(hThread);

            delete[] buffer;
        }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0);
        DeleteCriticalSection(&cs);
        return TRUE;
    }
    return FALSE;
}