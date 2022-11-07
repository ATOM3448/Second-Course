#include <iostream>
using namespace std;
//7 Вариант
int main()
{
	_int32 a = 1;			//EAX
	_int32 b = 2;			//EAX
	_int16 c = 3;			//AX

	_int32 d = 0;			//EAX  (c/a)*c+b  
	_int32 e = 0;			//EAX  (b-c)/a*c
	_asm //Нахождение d
	{
		mov ax, c;
		cwde;					//Помещаем С в EAX

		mov edx, 0;				//Помещаем в поле остатка 0
		div a;					//C/A
		mov d, eax;				//Сохраняем результат

		mov ax, c;				//Расширяем С для перемножения
		cwde;

		mul d;					//Перемножаем EAX на D

		add ax, word ptr b;		//Складываем младшие части
		add dx, word ptr b[2];	//Складываем старшие части

		mov word ptr d, ax;		//Сохраняем результат
		mov word ptr d[2], dx;	
	}
	
	cout << d << " - " << hex << d << endl;

	bool f;

	_asm //Нахождение e
	{
		mov ax, c;				//Вычитаем  C из B
		cwde;
		sbb b, eax; 
		mov eax, b;
		
		cmp eax, 0;				//Если EAX меньше чем 0
		jnl pos1;				

		neg eax;				//То меняем знак и ставим флаг
		mov f, 1;

		pos1:					//Иначе - нет

		mov edx, 0;				//Помещаем в поле остатка 0
		idiv a;					//Делим результат на A
		mov e, eax;				//Сохраняем результат

		mov ax, c;				//Расшираем C до dw
		cwde;

		imul e;					//Умножаем на C

		mov word ptr e, ax;		//Сохраняем результат
		mov word ptr e[2], dx;
	}

	if (f)
	{
		cout << dec << -e << " - " << hex << -e << endl;
	}
	else
	{
		cout << dec << e << " - " << hex << e << endl;
	}
	

	system("pause");
	return 0;
}