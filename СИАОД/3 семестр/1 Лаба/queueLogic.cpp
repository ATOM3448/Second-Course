#include <iostream>

using namespace std;

namespace myTaskLogic
{
	class MyQueue
	{
	public:
		explicit MyQueue() 
		{
			size = 100;
			start = 0;
			end = -1;
			queue = (int*)malloc(sizeof(int) * size);
		}
		~MyQueue()
		{
			delete[] queue;
			start = 0;
			end = 0;
		}

		//Поместить элемент в очередь
		void Push(int num)
		{
			if (end == (size - 1))
			{
				cout << "Очередь полна" << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				queue[++end] = num;
			}
		}

		//Изъять элемент из очереди
		int Pop()
		{
			if (start > end)
			{
				cout << "Очередь пуста" << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				return queue[start++];
			}
		}

		//Получение первого
		int Start()const
		{
			return queue[start];
		}

		//Является ли очередь пустой
		bool IsEmpty()const
		{
			if (start > end)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		short int size;
		short int start;
		short int end;
		int* queue;
	};
}