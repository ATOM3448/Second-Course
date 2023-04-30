#pragma once

#include <iostream>

namespace myTask
{
	class MyBaseClass
	{
	public:
		//Основной конструктор
		explicit MyBaseClass(unsigned int _rows, unsigned int _cols, unsigned int* _counter, double* _data = nullptr);

		//Деструктор
		~MyBaseClass();

		//Получить id
		int getId()const;

		//Получить значение счётчика
		virtual unsigned int getNextId() = 0;

		//Получить строки
		int getRows()const;

		//Вставить строки
		void setRows(int _in);

		//Получить колонки
		int getCols()const;

		//Вставить колонки
		void setCols(int _in);

		//Получить указатель на массив значений
		double* getData()const;

		//Вставить указатель на массив значений
		void setData(double* _in);

		//Максимум
		double max()const;

		//Минимум
		double min()const;

	protected:
		double* data;
		unsigned int rows;
		unsigned int cols;
		const int id;
	};
}