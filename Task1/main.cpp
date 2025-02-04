#define _CAT_SECURE_N0_WARNING
#include <iostream>
#include <tchar.h>

using namespace std;

bool ISPAL(_TCHAR* str) {
	int l = 0;
	int r = _tcsclen(str) - 1;

	for (int i = 0; i < _tcsclen(str)-1; i++)
	{
		if (str[l]==str[r])
		{
			l++;
			r--;
		}
		else
		{
			return false;
		}
	}
	return true;

}


void main()
{
	//_TCHAR szbuf3[15] = _TEXT("Hello,");
	//_tcscat(szbuf3, _TEXT("world!"));
	//wcout << szbuf3 << '\n';
	//cout << "The size of array: " << sizeof(szbuf3) << "bytes]n";

	_TCHAR str[10] = _TEXT("bob");
	wcout << ISPAL(str) << endl;

}