#pragma once 

#include "MyBaseClass.h"

namespace myTask
{
	class NewVector:MyBaseClass
	{
	private:
		static unsigned int counter;
	public:

		//Конструктор по умолчанию
		explicit NewVector();

		//Конструктор с параметрами
		NewVector(unsigned int _col, double* _data);

		//Конструктор копирующий
		NewVector(const NewVector& _in);

		//Конструктор перемещения
		NewVector(NewVector&& _in);

		//Получить значение счётчика
		unsigned int MyBaseClass::getNextId();

		//Переименовать
		//Проверка на возможность сложения
		bool CheckAdd(const NewVector& _in)const;

		//Переименовать
		//Проверка на возможность умножения
		bool CheckMul(const NewVector& _in)const;

		//Оператор вывода
		friend std::ostream& operator<<(std::ostream& _os, const NewVector& _in);

		//Оператор копирования
		NewVector& operator=(const NewVector& _in);

		//Оператор перемещения
		NewVector& operator=(NewVector&& _in);

		//Оператор +=
		NewVector& operator+=(const NewVector& _in);

		//Оператор -=
		NewVector& operator-=(const NewVector& _in);

		//Оператор *=
		NewVector& operator*=(const NewVector& _in);

		//Оператор *= скаляр
		NewVector& operator*=(const double _in);
	};

	//Переопределение оператора +
	NewVector operator+(const NewVector& _left, const NewVector& _right);

	//Переопределение оператора -
	NewVector operator-(const NewVector& _left, const NewVector& _right);

	//Переопределение оператора *
	NewVector operator*(const NewVector& _left, const NewVector& _right);

	//Переопределение оператора * на скаляр
	NewVector operator*(const NewVector& _left, const double _right);

}
