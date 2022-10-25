#include <iostream>

using namespace std;

namespace myTaskLogic
{
	class MyStack 
	{
	public:
		//Поместить элемент в стек
		void Push(int num)
		{
			Node* NewNode = new Node();
			if (NewNode)
			{
				(*NewNode).next = top;
				(*NewNode).data = num;
				top = NewNode;
			}
			else
			{
				cout << "Ошибка внесения элемента";
				exit(EXIT_FAILURE);
			}
		}

		//Изъять элемент из стека
		int Pop()
		{
			if (top)
			{
				int out = (*top).data;
				Node* newTop = (*top).next;
				delete[] top;
				top = newTop;
				return out;
			}
			else
			{
				cout << "Ошибка взятия элемента";
				exit(EXIT_FAILURE);
			}
		}

		//Получение верхнего значения в стеке
		int Top()const
		{
			return (*top).data;
		}

		//Является ли стек пустым
		bool IsEmpty()const
		{
			if (top)
			{
				return false;
			}
			else
			{
				return true;
			}
		}

	private:
		class Node
		{
		public:
			int data;
			Node* next;
			Node()
			{
				data = 0;
				next = NULL;
			}
		};

		Node* top = NULL;
	};
}