#include <iostream>

using namespace std;

namespace myTaskLogic
{
	class MyStack 
	{
	public:
		explicit MyStack()
		{
			size = 100;
			t = -1;
		}
		~MyStack()
		{
			delete[] stack;
			size = 0;
			t = 0;
		}

		//Поместить элемент в стек
		void Push(int num)
		{
			if (t == (size - 1))
			{
				cout << "Добавление элемента вызовет переполнение стека" << endl;
				exit(EXIT_FAILURE);
			}
			else 
			{
				stack[++t] = num;
			}
		}

		//Изъять элемент из стека
		int Pop()
		{
			if (t == -1)
			{
				cout << "Стек пуст и не может предоставить значение" << endl;
				exit(EXIT_FAILURE);
			}
			else
			{
				int out = stack[t--];
				return out;
			}
		}

		//Получение верхнего значения в стеке
		int Top()const
		{
			return stack[t];
		}

		//Является ли стек пустым
		bool IsEmpty()const
		{
			if (t == -1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}

	private:
		short int t;
		int size;
		int stack[100];
	};
}