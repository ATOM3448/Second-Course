#include "MyBaseClass.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace myTask
{
	MyBaseClass::MyBaseClass(unsigned int _rows, unsigned int _cols, unsigned int* _counter, double* _data) : id{(*_counter)++}
	{
		cout << "I'm constructor, for id: " << id << endl;

		data = (double*)malloc(sizeof(double) * _cols * _rows);

		rows = _rows;
		cols = _cols;

		if (_data)
		{
			for (unsigned int i = 0; i < cols * rows; i++)
			{
				data[i] = _data[i];
			}

			return;
		}

		for (unsigned int i = 0; i < cols * rows; i++)
		{
			data[i] = i;
		}
	}

	//Деконструктор
	MyBaseClass::~MyBaseClass()
	{
		cout << "I'm destrucor, for id: " << id << endl;

		if (data)
		{
			delete[] data;
		}
		
		rows = 0;
		cols = 0;
	}

	//Получить id
	int MyBaseClass::getId()const
	{
		return id;
	}

	//Получить строки
	int MyBaseClass::getRows()const
	{
		return rows;
	}

	//Вставить строки
	void MyBaseClass::setRows(int _in)
	{
		rows = _in;
	}

	//Получить колонки
	int MyBaseClass::getCols()const
	{
		return cols;
	}

	//Вставить колонки
	void MyBaseClass::setCols(int _in)
	{
		cols = _in;
	}

	//Получить указатель на массив данных
	double* MyBaseClass::getData()const
	{
		return data;
	}

	//Вставить указатель на массив данных
	void MyBaseClass::setData(double* _in)
	{
		data = _in;
	}

	//Получить максимум
	double MyBaseClass::max()const
	{
		double max = data[0];
		for (unsigned int i = 1; i < rows*cols; i++)
		{
			if (max < data[i])
			{
				max = data[i];
			}
		}

		return max;
	}

	//Получить минимум
	double MyBaseClass::min()const
	{
		double min = data[0];
		for (unsigned int i = 1; i < rows*cols; i++)
		{
			if (min > data[i])
			{
				min = data[i];
			}
		}

		return min;
	}
}