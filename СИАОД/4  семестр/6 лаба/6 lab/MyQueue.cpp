#include <iostream>
#include <fstream>
#include "MyQueue.h"

using namespace std;

namespace MyTask
{
	MyQueue::MyQueue()
	{
		head = nullptr;
	}

	MyQueue::~MyQueue()
	{
		while (head)
		{
			Node* next = head->next;
			delete[] head;
			head = next;
		}
	}

	void MyQueue::Push(int _num)
	{
		Node* newNode = new Node();
		
		if(!newNode)
		{
			cout << endl << "Ошибка выделения памяти" << endl;
			return;
		}

		newNode->num = _num;
		newNode->next = nullptr;

		if (!head)
		{
			head = newNode;
			return;
		}

		Node* place = head;
		while (place->next)
		{
			place = place->next;
		}
		place->next = newNode;
	}

	int MyQueue::Pop()
	{
		if (!head)
		{
			cout << endl << "Очередь пуста" << endl;
			return 0;
		}

		int out = head->num;
		
		Node* next = head->next;

		delete[] head;
		
		head = next;

		return out;
	}
}
