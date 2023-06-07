#pragma once

#include <iostream>

using namespace std;

namespace MyTask
{
	template<class T>
	class MyList
	{
	private:
		struct Node
		{
			T num;
			Node* next;
		};
		Node* head;
		int size;

	public:
		

		MyList()
		{
			head = nullptr;
			size = 0;
		}

		~MyList()
		{
			while (head)
			{
				Node* next = head->next;
				delete[] head;
				head = next;
			}
			size = 0;
		}

		void Push(T _num)
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

		Node* HeadNode()
		{
			return head;
		}

		T* Head()
		{
			return head->num;
		}

		int GetSize()
		{
			return size;
		}
	};
}