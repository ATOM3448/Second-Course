#include "Hash-table.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

namespace myLab
{
	MyHashTable::MyHashTable(int _size)
	{
		size = _size;
		table = new str[size];
		for (int i = 0; i < _size; i++)
		{
			table[i].data = "";
			table[i].status = 0;
		}
	}

	MyHashTable::~MyHashTable()
	{
		delete[] table;
	}

	unsigned int MyHashTable::hash_function(string _data)
	{
		unsigned int hash = 0;
		unsigned int key_size = _data.length();
		for (int i = key_size; i > 0; i--)
		{
			hash += _data[i - 1] * pow(2, i);
		}
		return hash;
	}

	bool MyHashTable::set_new(string _data)
	{
		unsigned int _hashValue = (int)hash_function(_data);
		bool flag = 1;
		for (int i = 0; i < (size); i++)
		{
			int position = (_hashValue + (i*i)) % size;
			if (table[position].data.empty())
			{
				cout << "count of attemps: " << i + 1 << endl;
				table[position].data = _data;
				table[position].status = 0;
				flag = 0;
				break;
			}
		}
		if (flag)
		{
			return 0;
		}
		return 1;
	}

	int MyHashTable::find_elem(string _data)
	{
		unsigned int _hashValue = (int)hash_function(_data);
		int position = (_hashValue) % size;
		if (table[position].data == _data)
		{
			cout << "count of attemps: " << 0 + 1 << endl;
			return position;
		}

		for (int i = 1; (i < size) && ((!table[position].data.empty()) || (table[position].status)); i++)
		{
			position = (_hashValue + (i*i)) % size;
			if (table[position].data == _data)
			{
				cout << "count of attemps: " << i + 1<< endl;
				return position;
			}
		}

		cout << "Not found";
		return -1;
	}

	bool MyHashTable::delete_elem(string _data)
	{
		int position = find_elem(_data);
		if (position == -1)
		{
			return 0;
		}

		table[position].data = "";
		table[position].status = 1;
		cout << "was delete" << endl;
		return 1;
	}

	bool MyHashTable::print_table()
	{
		for (int i = 0; i < size; i++)
		{
			cout << setw(10) << table[i].data << " | " << table[i].status << endl;
		}
		return 0;
	}
}