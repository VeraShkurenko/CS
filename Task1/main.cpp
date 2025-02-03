#define _CAT_SECURE_N0_WARNING
#include <iostream>
#include <tchar.h>

using namespace std;

void main()
{
	_TCHAR szbuf3[15] = _TEXT("Hello,");
	_tcscat(szbuf3, _TEXT("world!"));
	wcout << szbuf3 << '\n';
	cout << "The size of array: " << sizeof(szbuf3) << "bytes]n";



}