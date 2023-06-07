#include <iostream>
#include <locale.h>
#include "MyGraph.h"

using namespace std;
using namespace MyTask;

/*
Напишите программу, которая с помощью алгоритма Крускала находит минимальное покрывающее дерево для произвольного связного неориентированного графа, заданного списками смежности. 
Выведите на экран ребра, вошедшие в искомое дерево. 
Предусмотрите ввод данных из файла.
После завершения работы с динамическими структурами данных необходимо освободить занимаемую ими память.
*/

int main()
{
	setlocale(LC_ALL, "rus");

	MyGraph graph;

	graph.ImportFromFile("File.txt");
	graph.ImportValues("Values.txt");

	graph.Kruskal();

	system("pause");

	return 0;
}
