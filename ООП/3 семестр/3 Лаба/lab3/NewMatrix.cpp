#include "NewMatrix.h"
#include <iostream>
#include <iomanip>

using namespace std;

namespace myTask
{
	//Счётчик id
	unsigned int NewMatrix::counter = 0;

	//Конструктор по умолчанию
	NewMatrix::NewMatrix() : MyBaseClass(3, 3, &counter, nullptr)
	{
		cout << "Constructor #1 for id: " << id << endl;
	}

	//Конструктор с параметрами
	NewMatrix::NewMatrix(unsigned int _row, unsigned int _col, double* _data) : MyBaseClass(_row, _col, &counter, _data)
	{
		cout << "Constructor #2 for id: " << id << endl;
	}

	//Конструктор копирующий
	NewMatrix::NewMatrix(const NewMatrix& _in) : MyBaseClass(_in.rows, _in.cols, &counter, _in.data)
	{
		cout << "Constructor #3 for id: " << id << endl;
	}

	//Конструктор перемещения
	NewMatrix::NewMatrix(NewMatrix&& _in) : MyBaseClass(_in.rows, _in.cols, &counter, _in.data)
	{
		_in.rows = 0;
		_in.cols = 0;
		_in.data = nullptr;

		cout << "Constructor #4 for id: " << id << endl;
	}

	//Получить значение счётчика
	unsigned int NewMatrix::getNextId()
	{
		return counter;
	}

	//Проверка на возможность умножения
	bool NewMatrix::CheckMul(const NewMatrix& _right)const
	{
		if (rows == _right.getCols())
		{
			return 1;
		}
		return 0;
	}

	//Оператор умножения
	NewMatrix& NewMatrix::operator*=(const NewMatrix& _right)
	{
		if (!CheckMul(_right))
		{
			throw logic_error{ "Данные матрицы перемножать нельзя" };
		}

		double* buf = _right.getData();

		double* newData = new double[rows*_right.getCols()];

		unsigned int _cols = _right.getCols();
		unsigned int _rows = _right.getRows();
		double* _data = _right.getData();

		for (unsigned int i = 0; i < rows; i++)
		{
			for (unsigned int j = 0; j < _cols; j++)
			{
				newData[i*_cols + j] = 0;
				for (unsigned int k = 0; k < cols; k++)
				{
					newData[i*_cols + j] += (data[i*cols + k] * _data[k * _cols + j]);
				}
			}
		}

		delete[] data;

		data = newData;

		cols = _right.getCols();

		return *this;
	}

	//Проверка возможности сложения
	bool NewMatrix::CheckAdd(const NewMatrix& _in)const
	{
		if ((this->rows == _in.rows) && (this->cols == _in.cols))
		{
			return 1;
		}

		return 0;
	}

	//Переопределение оператора <<
	ostream& operator<<(ostream& _os, const NewMatrix& _in)
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
	NewMatrix& NewMatrix::operator=(const NewMatrix& _in)
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
	NewMatrix& NewMatrix::operator=(NewMatrix&& _in)
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
	NewMatrix& NewMatrix::operator+=(const NewMatrix& _in)
	{
		if (!CheckAdd(_in))
		{
			throw logic_error{ "Данные матрицы складывать нельзя" };
		}

		for (unsigned int i = 0; i < cols * rows; i++)
		{
			data[i] += _in.data[i];
		}

		return *this;
	}

	//Оператор -=
	NewMatrix& NewMatrix::operator-=(const NewMatrix& _in)
	{
		if (!CheckAdd(_in))
		{
			throw logic_error{ "Данные матрицы складывать нельзя" };
		}

		for (unsigned int i = 0; i < cols * rows; i++)
		{
			data[i] -= _in.data[i];
		}

		return *this;
	}

	//Оператор *= скаляр
	NewMatrix& NewMatrix::operator *= (const double _in)
	{
		for (unsigned int i = 0; i < rows*cols; i++)
		{
			data[i] *= _in;
		}

		return *this;
	}

	//Переопределение оператора +
	NewMatrix operator+(const NewMatrix& _left, const NewMatrix& _right)
	{
		if (!_left.CheckAdd(_right))
		{
			throw logic_error{ "Данные матрицы складывать нельзя" };
		}

		NewMatrix toOut(_left);

		return toOut += _right;
	}

	//Переопределение оператора -
	NewMatrix operator-(const NewMatrix& _left, const NewMatrix& _right)
	{
		if (!_left.CheckAdd(_right))
		{
			throw logic_error{ "Данные матрицы вычитать нельзя" };
		}

		NewMatrix toOut(_left);

		return toOut -= _right;
	}

	//Переопределение оператора *
	NewMatrix operator*(const NewMatrix& _left, const NewMatrix& _right)
	{
		if (!_left.CheckMul(_right))
		{
			throw logic_error{ "Данные матрицы умножать нельзя" };
		}

		NewMatrix toOut(_left);

		return toOut *= _right;
	}

	//Переопределение оператора * на скаляр
	NewMatrix operator*(const NewMatrix& _left, const double _right)
	{
		NewMatrix toOut(_left);

		return toOut *= _right;
	}
}