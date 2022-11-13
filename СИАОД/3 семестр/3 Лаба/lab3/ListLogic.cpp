#include <iostream>
#include <string>
using namespace std;

namespace myTask
{
	struct Node
	{
		string info;
		Node* next;
		Node* last;
	};
	
	class MyList
	{
	public:
		//Голова и хвост
		Node* head;
		Node* tail;

		//Инициализация
		MyList()
		{
			head = NULL;
			tail = NULL;
		}

		~MyList()
		{
			Node* x = head;
			while (x)
			{
				Node* next = (*x).next;
				(*x).info = "";
				(*x).last = NULL;
				(*x).next = NULL;
				x = next;
			}
		}
		
		//Функция вставки перед узлом
		void insertBefore(Node* node, string newData)
		{
			Node* newNode = new Node;
			(*newNode).info = newData;
			(*newNode).next = node;
			if ((*node).last)
			{
				(*newNode).last = (*node).last;
				(*(*node).last).next = newNode;
			}
			else
			{
				(*newNode).last = NULL;
				head = newNode;
			}
			(*node).last = newNode;
		}

		//Функция вставки после узла
		void insertAfter(Node* node, string newData)
		{
			Node* newNode = new Node;
			(*newNode).info = newData;
			(*newNode).last = node;
			if ((*node).next)
			{
				(*newNode).next = (*node).next;
				(*(*node).next).last = newNode;
			}
			else
			{
				(*newNode).next = NULL;
				tail = newNode;
			}
			(*node).next = newNode;
		}

		//Функция вставки узла в начало, возможно пустого списка
		void insertBeginning(string newData)
		{
			if (head)
			{
				insertBefore(head, newData);
			}
			else
			{
				head = new Node;
				(*head).info = newData;
				(*head).next = NULL;
				(*head).last = NULL;
				tail = head;
			}
		}

		//Функция вставки узла в конец
		void insertEnd(string newData)
		{
			if (tail)
			{
				insertAfter(tail, newData);
			}
			else
			{
				insertBeginning(newData);
			}
		}

		//Функция поиска(с начала) элемента из списка
		Node* findAtStart(string data)
		{
			Node* answer = head;

			while (answer)
			{
				if ((*answer).info == data)
				{
					return answer;
				}

				answer = (*answer).next;
			}

			cout << "Элемент не найден";
			exit(EXIT_FAILURE);
		}

		//Функция поиска(с конца) элемента из списка
		Node* findAtEnd(string data)
		{
			Node* answer = tail;

			while (answer)
			{
				if ((*answer).info == data)
				{
					return answer;
				}

				answer = (*answer).last;
			}

			cout << "Элемент не найден";
			exit(EXIT_FAILURE);
		}

		//Функция взятия из списка
		string remove(string data)
		{
			Node* node = findAtStart(data);

			if (node == head)
			{
				if ((*node).next) 
				{
					head = (*node).next;
					(*head).last = NULL;
					string out = (*node).info;
					delete[] node;
					return out;
				}
				else
				{
					head = NULL;
					tail = NULL;
					string out = (*node).info;
					delete[] node;
					return out;
				}
			}
			else
			{
				if (node == tail)
				{
					if ((*node).last)
					{
						tail = (*node).last;
						(*tail).next = NULL;
						string out = (*node).info;
						delete[] node;
						return out;
					}
					else
					{
						head = NULL;
						tail = NULL;
						string out = (*node).info;
						delete[] node;
						return out;
					}
				}
				else
				{
					(*(*node).last).next = (*node).next;
					(*(*node).next).last = (*node).last;
					string out = (*node).info;
					delete[] node;
					return out;
				}
			}
		}

		//Функция взятия из списка (первого)
		string remove()
		{
			Node* node = head;
			if (node)
			{

				if ((*node).next)
				{
					head = (*node).next;
					(*head).last = NULL;
					string out = (*node).info;
					delete[] node;
					return out;
				}
				else
				{
					head = NULL;
					tail = NULL;
					string out = (*node).info;
					delete[] node;
					return out;
				}
			}
			else
			{
				return NULL;
			}
		}
	};
}