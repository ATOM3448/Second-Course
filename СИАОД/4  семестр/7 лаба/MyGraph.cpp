#include <iostream>
#include <fstream>
#include "MyList.cpp"
#include "MyGraph.h"

using namespace std;

namespace MyTask
{
	MyGraph::MyGraph()
	{
		edges = nullptr;
		values = nullptr;
		valuesSort = nullptr;
		edgesCount = 0;
		count = 0;
	}

	MyGraph::~MyGraph()
	{
		delete[] edges;
		count = 0;
	}

	void MyGraph::ImportFromFile(const char* path)
	{
		ifstream f(path);

		if (!f.is_open())
		{
			cout << endl << "Ошибка чтения файла" << endl;
			return;
		}

		f >> count;

		edges = (MyList<int>**)malloc(sizeof(MyList<int>*) * count);

		values = (int**)malloc(sizeof(int*) * count);

		for (int i = 0; i < count; i++)
		{
			edges[i] = new MyList<int>();

			values[i] = (int*)malloc(sizeof(int) * count);
			for (int j = 0; j < count; j++)
			{
				values[i][j] = -1;
			}

			int buf = 0;

			f >> buf;

			while (buf != -1)
			{
				edges[i]->Push(buf);
				f >> buf;
			}
		}
	}

	void MyGraph::ImportValues(const char* _path)
	{
		ifstream f(_path);

		if (!f.is_open())
		{
			cout << endl << "Ошибка чтения файла" << endl;
			return;
		}

		int _i;
		int _j;
		int value;
		while (f >> _i)
		{
			f >> _j;
			f >> value;

			values[_i-1][_j-1] = value;
			edgesCount++;
		}

		// Сортировка по весу
		// 
		// Выделяем память под массив и переносим ребра значения которых не -1
		valuesSort = (int**)malloc(sizeof(int*) * edgesCount);
		int counter = 0;
		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count; j++)
			{
				if (values[i][j] != -1)
				{
					valuesSort[counter] = (int*)malloc(sizeof(int) * 3);
					valuesSort[counter][0] = i;
					valuesSort[counter][1] = j;
					valuesSort[counter++][2] = values[i][j];
				}
			}
		}

		// Сортируем
		for (int i = 0; i < edgesCount; i++)
		{
			for (int j = i + 1; j < edgesCount; j++)
			{
				if (valuesSort[i][2] > valuesSort[j][2])
				{
					for (int k = 0; k < 3; k++)
					{
						int buf = valuesSort[i][k];
						valuesSort[i][k] = valuesSort[j][k];
						valuesSort[j][k] = buf;
					}
				}
			}
		}
	}

	void MyGraph::Kruskal()
	{
		// Массив, отражающий пару "узел - корень подмножества, хранящее узел"
		int* coll = (int*)malloc(sizeof(int) * count);
		for (int i = 0; i < count; i++)
		{
			coll[i] = i;
		}

		// Счётчик найденных ребер
		int counter = 0;

		int sum = 0;

		// Ищем ребра, вошедшие в дерево
		for (int k = 0; counter != (count-1); k++)
		{
			if (coll[valuesSort[k][0]] != coll[valuesSort[k][1]])
			{
				int buf = coll[valuesSort[k][1]];
				for (int i = 0; i < count; i++)
				{
					if (coll[i] == buf)
					{
						coll[i] = valuesSort[k][0];
					}
				}
				sum += valuesSort[k][2];
				cout << valuesSort[k][0]+1 << " - " << valuesSort[k][1]+1 << endl;
				counter++;
			}
		}
		cout << "Sum: " << sum << endl;
	}
}