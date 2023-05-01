#include <iostream>
#include <fstream>
#include "MyList.h"
#include "MyQueue.h";
#include "MyGraph.h"

using namespace std;

namespace MyTask
{
	MyGraph::MyGraph()
	{
		edges = nullptr;
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

		edges = (MyList**)malloc(sizeof(MyList*) * count);

		for (int i = 0; i < count; i++)
		{
			edges[i] = new MyList();

			int buf = 0;

			f >> buf;

			while (buf != -1)
			{
				edges[i]->Push(buf);
				f >> buf;
			}
		}
	}

	int MyGraph::GetCount()
	{
		return count;
	}

	int MyGraph::Component(int _start, int last, int* _way)
	{
		MyQueue* ways = edges[_start-1]->GetQueue();

		int next = 0;
		int myValue = _start;
		_way[_start-1] = myValue;

		while (next = ways->Pop())
		{
			if (next == last)
			{
				continue;
			}

			if (_way[next-1])
			{
				if(_way[next-1] < myValue)
				{
					myValue = _way[next-1];
				}
				continue;
			}

			//Идем к следующему узлу
			int nextValue = Component(next, _start, _way);

			//Проверяем нужно ли менять вес
			if (nextValue < myValue)
			{
				myValue = nextValue;
			}
		}

		//Возвращаем значение
		_way[_start-1] = myValue;
		return myValue;
	}

	void MyGraph::Components()
	{
		//Массив весов(и обозначение не пройденых) узлов
		int* way = (int*)malloc(sizeof(int) * count);
		for (int i = 0; i < count; i++)
		{
			way[i] = 0;
		}

		Component(1, -1, way);

		//Считаем количество компонент
		int* comp = (int*)malloc(sizeof(int) * count);
		int countComp = 0;

		for (int i = 0; i < count; i++)
		{
			bool flag = true;

			for (int j = 0; j < countComp; j++)
			{
				if (comp[j] == way[i])
				{
					flag = false;
					break;
				}
			}

			if (flag)
			{
				comp[countComp++] = way[i];
			}
		}

		//Выводим компоненты
		for (int i = 0; i < countComp; i++)
		{
			cout << endl << "Компонента " << i+1 << ":";
			for (int j = 0; j < count; j++)
			{
				if (way[j] == comp[i])
				{
					cout << " " << j+1;
				}
			}
		}

		cout << endl;

		//Чистим лишнее
		delete[] comp;
		delete[] way;
	}
}