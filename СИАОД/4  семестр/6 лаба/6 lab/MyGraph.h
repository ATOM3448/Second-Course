#pragma once

#include "MyList.h"

namespace MyTask
{
	class MyGraph
	{
	private:
		MyList** edges;
		int count;

		int Component(int _start, int last, int* _way);

	public:
		MyGraph();

		~MyGraph();

		void ImportFromFile(const char* path);

		int GetCount();

		void Components();
	};
}