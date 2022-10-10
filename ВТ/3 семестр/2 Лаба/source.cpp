#include <iostream>
using namespace std;
//7 Вариант

int main()
{
	//Числа только положительные 2 байт
	short int a = 0x1122;
	short int b = 0x3377;
	int c = 0x55667788;

	cout << "a - " << a << "b - " << b << "c - " << c << endl;
	
	_asm
	{
		mov AH, byte ptr b[1];
		xchg AH, byte ptr a[1];
		xchg AH, byte ptr c[3];
		xchg AH, byte ptr c[0];
		xchg AH, byte ptr b[0];
		mov byte ptr b[1], AH;
		mov AH, byte ptr c[1];
		xchg AH, byte ptr a[0];
		xchg AH, byte ptr c[2];
		mov byte ptr c[1], AH;
	}

	cout << "a - " << a << "b - " << b << "c - " << c << endl;

	system("pause");

	return 0;
}