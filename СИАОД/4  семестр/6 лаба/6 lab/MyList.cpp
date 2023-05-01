#include <iostream>
#include "MyList.h"
#include "MyQueue.h"

using namespace std;

namespace MyTask
{
	MyList::MyList()
	{
		head = nullptr;
		size = 0;
	}

	MyList::~MyList()
	{
		while (head)
		{
			Node* next = head->next;
			delete[] head;
			head = next;
		}
		size = 0;
	}

	void MyList::Push(int _num)
	{
		Node* newNode = new Node();

		if (!newNode)
		{
			cout << endl << "Ошибка выделения памяти" << endl;
			return;
		}

		newNode->num = _num;
		newNode->next = nullptr;

		if (!head)
		{
			head = newNode;
			size++;
			return;
		}

		Node* place = head;
		while (place->next)
		{
			place = place->next;
		}
		place->next = newNode;
		size++;
	}

	int MyList::Head()
	{
		return head->num;
	}

	int MyList::GetSize()
	{
		return size;
	}

	MyQueue* MyList::GetQueue()
	{
		MyQueue* QEdges = new MyQueue();

		Node* next = head->next;

		while (next)
		{
			QEdges->Push(next->num);

			next = next->next;
		}

		return QEdges;
	}

	bool MyList::Find(int _num)
	{
		Node* place = head;
		while (place)
		{
			if (place->num == _num)
			{
				return true;
			}

			place = place->next;
		}
		return false;
	}
}