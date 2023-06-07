#pragma once

#include "MyList.cpp"

namespace MyTask
{
	class MyGraph
	{
	private:
		MyList<int>** edges;
		int count;
		int edgesCount;
		int** values;
		int** valuesSort;

	public:
		MyGraph();

		~MyGraph();

		void ImportFromFile(const char* path);

		void ImportValues(const char* _path);

		void Kruskal();
	};
}