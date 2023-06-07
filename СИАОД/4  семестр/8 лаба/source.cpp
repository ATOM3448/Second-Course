#include <iostream>
#include <fstream>
#include <ctime>
#include <locale.h>

using namespace std;

/*
2.
Пусть даны три файла вещественных чисел, состоящих из 100, 1000 и 10000 чисел.
Выполнить сортировку данных с помощью метода пирамидальной сортировки.
Подсчитать количество операций сравнения для каждого из трех файлов.
*/

void FileGenerator()
{
	srand(time(NULL));
	ofstream f100("D:/СИАОД/4 семестр/8 лаба/lab8/lab8/100.txt", ios_base::trunc);
	for (int i = 0; i < 100; i++)
	{
		f100 << rand();
		f100 << '\n';
	}
	f100.close();

	ofstream f1000("D:/СИАОД/4 семестр/8 лаба/lab8/lab8/1000.txt", ios_base::trunc);
	for (int i = 0; i < 1000; i++)
	{
		f1000 << rand();
		f1000 << '\n';
	}
	f1000.close();

	ofstream f10000("D:/СИАОД/4 семестр/8 лаба/lab8/lab8/10000.txt", ios_base::trunc);
	for (int i = 0; i < 10000; i++)
	{
		f10000 << rand();
		f10000 << '\n';
	}
	f10000.close();
}

int* MassiveCreater(char* _path, int _size)
{
	int* toOut = (int*)malloc(sizeof(int) * _size);

	ifstream f(_path);

	for (int i = 0; i < _size; i++)
	{
		f >> toOut[i];
	}

	return toOut;
}

void Balance(int* _nums, int _size, int _node, int* _counter)
{
	int max = _node;

	int l = 2 * _node + 1;
	int r = 2 * _node + 2;

	if ((l < _size) && (_nums[max] < _nums[l]))
	{
		max = l;
	}

	if ((r < _size) && (_nums[max] < _nums[r]))
	{
		max = r;
	}
	if (max != _node)
	{
		int buf = _nums[_node];
		_nums[_node] = _nums[max];
		_nums[max] = buf;

		Balance(_nums, _size, max, _counter);
	}

	*_counter += 3;
}

void Task(int* _nums, int _size, int* _counter)
{
	// Начальная сортировка
	for (int i = _size / 2 - 1; i >= 0; i--)
	{
		Balance(_nums, _size, i, _counter);
	}

	// Сортируем
	for (int i = _size - 1; i >= 0; i--)
	{
		int buf = _nums[0];
		_nums[0] = _nums[i];
		_nums[i] = buf;

		Balance(_nums, i, 0, _counter);
	}
}

int main()
{
	setlocale(LC_ALL, "rus");

	for (int size = 100; size != 100000; size *= 10)
	{
		int counter = 0;
		int* nums = nullptr;

		ofstream f;

		if (size == 100)
		{
			f = ofstream("D:/СИАОД/4 семестр/8 лаба/lab8/lab8/result_100.txt", ios_base::trunc);
			nums = MassiveCreater("100.txt", size);
		}
		
		if (size == 1000)
		{
			f = ofstream("D:/СИАОД/4 семестр/8 лаба/lab8/lab8/result_1000.txt", ios_base::trunc);
			nums = MassiveCreater("1000.txt", size);
		}
		
		if (size == 10000)
		{
			f = ofstream("D:/СИАОД/4 семестр/8 лаба/lab8/lab8/result_10000.txt", ios_base::trunc);
			nums = MassiveCreater("10000.txt", size);
		}
		
		Task(nums, size, &counter);

		cout << size << counter << endl;

		for (int i = 0; i < size; i++)
		{
			f << nums[i];
			f << '\n';
		}
	}

	system("pause");

	return 0;
}