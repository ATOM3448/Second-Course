#pragma once

namespace MyTask
{
	class MyQueue
	{
	private:
		struct Node
		{
			int num;
			Node* next;
		};

		Node* head;

	public:
		MyQueue();
		
		~MyQueue();

		void Push(int _num);

		int Pop();
	};
}