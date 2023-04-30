#pragma once

#include "MyBaseClass.h"

namespace myTask
{
	class NewMatrix:MyBaseClass
	{
	private:
		static unsigned int counter;
	public:

		//Конструктор по умолчанию
		explicit NewMatrix();

		//Конструктор с параметрами
		NewMatrix(unsigned int _col, unsigned int _row, double* _data);

		//Конструктор копирующий
		NewMatrix(const NewMatrix& _in);

		//Конструктор перемещения
		NewMatrix(NewMatrix&& _in);

		//Получить значение счётчика
		unsigned int MyBaseClass::getNextId();

		//Переименовать
		//Проверка на возможность сложения
		bool CheckAdd(const NewMatrix& _in)const;

		//Переименовать
		//Проверка на возможность умножения
		bool CheckMul(const NewMatrix& _in)const;

		//Оператор вывода
		friend std::ostream& operator<<(std::ostream& _os, const NewMatrix& _in);

		//Оператор копирования
		NewMatrix& operator=(const NewMatrix& _in);

		//Оператор перемещения
		NewMatrix& operator=(NewMatrix&& _in);

		//Оператор +=
		NewMatrix& operator+=(const NewMatrix& _in);

		//Оператор -=
		NewMatrix& operator-=(const NewMatrix& _in);

		//Оператор *=
		NewMatrix& operator*=(const NewMatrix& _in);

		//Оператор *= скаляр
		NewMatrix& operator*=(const double _in);
	};

	//Переопределение оператора +
	NewMatrix operator+(const NewMatrix& _left, const NewMatrix& _right);

	//Переопределение оператора -
	NewMatrix operator-(const NewMatrix& _left, const NewMatrix& _right);

	//Переопределение оператора *
	NewMatrix operator*(const NewMatrix& _left, const NewMatrix& _right);

	//Переопределение оператора * на скаляр
	NewMatrix operator*(const NewMatrix& _left, const double _right);

}
