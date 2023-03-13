#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>
#include "Hash-table.h"

using namespace std;
using namespace myLab; 

int main()
{ 

	MyHashTable table(50);

	ifstream f("file.txt");

	if (!f.is_open())
	{
		cout << "error";
		return 0;
	}

	string word;

	while (f >> word)
	{
		if (!table.set_new(word))
		{
			cout << "there is no place" << endl;
		}
	}

	table.print_table();

	cout << endl;

	//При записи 15, встречается колизия с 8, удалим её, чтобы посмотреть как функция найдет 15 в таблице, с таким пробелом
	cout << table.find_elem("fifteen") << endl;
	
	table.delete_elem("eight");

	cout << table.find_elem("fifteen") << endl;

	cout << endl;

	table.print_table();

	system("pause");

	return 0; 
}