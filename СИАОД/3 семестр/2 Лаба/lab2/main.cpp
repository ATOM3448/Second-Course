#include <iostream>
#include <locale.h>
#include <fstream>

#include "stackLogic.cpp"

using namespace std;
using namespace myTaskLogic;

struct Record
{
	int num;
	char operation;
};

int main()
{
	setlocale(LC_ALL, "rus");

	MyStack stack;
	Record rec = {-1, '?'};

	ifstream f("File.txt");

	if (f.is_open())
	{
		f >> rec.num;
		stack.Push(rec.num);
		rec.num = -1;

		while (f >> rec.num >> rec.operation)
		{
			if (rec.num != -1)
			{
				stack.Push(rec.num);
				rec.num = -1;
			}

			switch (rec.operation)
			{
			case '+':
				stack.Push(stack.Pop() + stack.Pop());
				break;
			case '-':
			{
				stack.Push((-stack.Pop()) + stack.Pop());
				break;
			}
			case '*':
				stack.Push(stack.Pop() * stack.Pop());
				break;
			case '/':
			{
				int a = stack.Pop();
				int b = stack.Pop();
				stack.Push(b / a);
				break;
			}
			default:
				break;
			}
		}

		cout << (int)stack.Pop() << endl;
	}
	else
	{
		cout << "error" << endl;
	}

	system("pause");

	return 0;
}
