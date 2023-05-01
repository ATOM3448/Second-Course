#pragma once
#include "MyQueue.h"

namespace MyTask
{
	class MyList
	{
	private:
		struct Node
		{
			int num;
			Node* next;
		};

		Node* head;
		int size;

	public:
		MyList();

		~MyList();

		void Push(int _num);

		int Head();

		int GetSize();

		MyQueue* GetQueue();

		bool Find(int _num);
	};
}