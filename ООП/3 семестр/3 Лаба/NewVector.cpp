#include "NewVector.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace myTask
{
	//Счётчик id
	unsigned int NewVector::counter = 0;

	//Конструктор по умолчанию
	NewVector::NewVector() : MyBaseClass(1, 3, &counter, nullptr)
	{
		cout << "Constructor #1 for id: " << id << endl;
	}

	//Конструктор с параметрами
	NewVector::NewVector(unsigned int _col, double* _data) : MyBaseClass(1, _col, &counter, _data)
	{
		cout << "Constructor #2 for id: " << id << endl;
	}

	//Конструктор копирующий
	NewVector::NewVector(const NewVector& _in) : MyBaseClass(_in.rows, _in.cols, &counter, _in.data)
	{
		cout << "Constructor #3 for id: " << id << endl;
	}

	//Конструктор перемещения
	NewVector::NewVector(NewVector&& _in) : MyBaseClass(_in.rows, _in.cols, &counter, _in.data)
	{
		_in.rows = 0;
		_in.cols = 0;
		_in.data = nullptr;

		cout << "Constructor #4 for id: " << id << endl;
	}
	
	//Получить значение счётчика
	unsigned int NewVector::getNextId()
	{
		return counter;
	}

	//Проверка на возможность умножения
	bool NewVector::CheckMul(const NewVector& _right)const
	{
		if (cols == _right.getCols())
		{
			return 1;
		}

		if (rows == _right.getCols())
		{
			return 1;
		}

		return 0;
	}

	//Оператор умножения
	NewVector& NewVector::operator*=(const NewVector& _right)
	{
		if (!CheckMul(_right))
		{
			throw logic_error{ "Данные вектора перемножать нельзя" };
		}

		double* buf = _right.getData();

		if (_right.getRows() == 1)
		{
			for (unsigned int i = 0; i < cols; i++)
			{
				data[i] *= buf[i];
			}

			return *this;
		}

		return *this;
	}

	//Проверка возможности сложения
	bool NewVector::CheckAdd(const NewVector& _in)const
	{
		if ((this->rows == _in.rows) && (this->cols == _in.cols))
		{
			return 1;
		}

		return 0;
	}

	//Переопределение оператора <<
	ostream& operator<<(ostream& _os, const NewVector& _in)
	{
		double* buf = _in.getData();
		unsigned int row = _in.getRows();
		unsigned int col = _in.getCols();
		for (unsigned int i = 0; i < row; i++)
		{
			_os << endl;
			for (unsigned int j = 0; j < col; j++)
			{
				_os << setw(6) << fixed << setprecision(3) << buf[i * col + j] << " ";
			}
		}
		_os << endl << endl;
		return _os;
	}

	//Оператор копирования
	NewVector& NewVector::operator=(const NewVector& _in)
	{
		if (!((rows == _in.rows) && (cols == _in.cols)))
		{
			delete[] data;

			rows = _in.rows;
			cols = _in.cols;

			data = (double*)malloc(sizeof(double) * cols * rows);
		}

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < cols; j++)
			{
				data[i * cols + j] = _in.data[i * cols + j];
			}
		}

		return *this;
	}

	//Оператор перемещения
	NewVector& NewVector::operator=(NewVector&& _in)
	{

		double* buf = _in.data;
		_in.data = data;
		data = buf;

		unsigned int bufInt = _in.rows;
		_in.rows = rows;
		rows = bufInt;

		bufInt = _in.cols;
		_in.cols = cols;
		cols = bufInt;

		return *this;
	}

	//Оператор +=
	NewVector& NewVector::operator+=(const NewVector& _in)
	{
		if (!CheckAdd(_in))
		{
			throw logic_error{ "Данные вектора складывать нельзя" };
		}

		for (unsigned int i = 0; i < cols * rows; i++)
		{
			data[i] += _in.data[i];
		}

		return *this;
	}

	//Оператор -=
	NewVector& NewVector::operator-=(const NewVector& _in)
	{
		if (!CheckAdd(_in))
		{
			throw logic_error{ "Данные вектора нельзя вычитать" };
		}

		for (unsigned int i = 0; i < cols * rows; i++)
		{
			data[i] -= _in.data[i];
		}

		return *this;
	}

	//Оператор *= скаляр
	NewVector& NewVector::operator *= (const double _in)
	{
		for (unsigned int i = 0; i < rows*cols; i++)
		{
			data[i] *= _in;
		}

		return *this;
	}

	//Переопределение оператора +
	NewVector operator+(const NewVector& _left, const NewVector& _right)
	{
		if (!_left.CheckAdd(_right))
		{
			throw logic_error{ "Данные матрицы складывать нельзя" };
		}

		NewVector toOut(_left);

		return toOut += _right;
	}

	//Переопределение оператора -
	NewVector operator-(const NewVector& _left, const NewVector& _right)
	{
		if (!_left.CheckAdd(_right))
		{
			throw logic_error{ "Данные матрицы вычитать нельзя" };
		}

		NewVector toOut(_left);

		return toOut -= _right;
	}

	//Переопределение оператора *
	NewVector operator*(const NewVector& _left, const NewVector& _right)
	{
		if (!_left.CheckMul(_right))
		{
			throw logic_error{ "Данные матрицы умножать нельзя" };
		}

		NewVector toOut(_left);

		return toOut *= _right;
	}

	//Переопределение оператора * на скаляр
	NewVector operator*(const NewVector& _left, const double _right)
	{
		NewVector toOut(_left);

		return toOut *= _right;
	}
}