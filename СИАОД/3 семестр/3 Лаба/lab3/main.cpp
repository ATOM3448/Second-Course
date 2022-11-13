#include <iostream>
#include <locale.h>
#include <fstream>

#include "ListLogic.cpp"

using namespace std;
using namespace myTask;


int main()
{
	setlocale(LC_ALL, "rus");

	MyList list;

	ifstream f("File.txt");

	if (f.is_open())
	{
		string str;
		while (f >> str)
		{
			list.insertEnd(str);
		}
		Node* x = list.head;
		int count = 0;
		while (x!=list.tail)
		{
			if ((*x).info[0] == (*(*x).next).info[0])
			{
				count++;
			}
			x = (*x).next;
		}
		cout << count << endl;
	}
	else
	{
		cout << "error" << endl;
	}

	system("pause");

	return 0;
}
