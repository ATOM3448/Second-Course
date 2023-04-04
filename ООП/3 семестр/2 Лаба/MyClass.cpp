#include <iostream>
#include <iomanip>
#include <string>
#include "MyClass.h"
using namespace std;

namespace myNameSpaces
{
	int MyMatrix::newID = 0;
	//1 Конструктор(с заданными размерами, компонентами)(по умолчанию)
	MyMatrix::MyMatrix(unsigned int _rows, unsigned int _cols, const double* _data) :id{ newID++ }
	{
		if ((_cols == 0) && (_data != NULL))
		{

			throw logic_error{"Class MyMatrix, constructor #1, an array with no cols size was passed for id" + to_string(id)};
		}

		cout << "I'm constructor #1, for id: " << id << endl;
		
		if (!_rows)
		{
			createMatrix(5, 5);
		}
		else
		{
			if (!_cols)
			{
				_cols = _rows;
			}
			createMatrix(_rows, _cols, _data);
		}

		cout << "My values: " << endl;

		cout << *this;	
	}

	//2 Конструктор(копирование)
	MyMatrix::MyMatrix(const MyMatrix& _early) :id{ newID++ }
	{
		cout << "I'm construcor #2, for id: " << id << "\n";

		rows = _early.rows;
		cols = _early.cols;

		data = new double[rows * cols];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i * cols + j] = _early.data[i * cols + j];
			}
		}

		cout << "My values: " << endl;

		cout << *this;
	}

	//3 Конструктор(с заданными размерами, компонентами)(по умолчанию)
	MyMatrix::MyMatrix(unsigned int _size, const double* _data) : MyMatrix(_size, _size, _data)
	{
		cout << "\nI'm constructor #3, for id: " << id << endl;

		cout << "My values: " << endl;

		cout << *this;
	}

	//4 Конструктор(swap)
	MyMatrix::MyMatrix(MyMatrix&& _other) :id{ newID++ }
	{
		cout << "\nI'm constructor #4, for id: " << id << endl;

		rows = _other.rows;
		cols = _other.cols;
		data = _other.data;

		_other.data = nullptr;
		_other.rows = 0;
		_other.cols = 0;

		cout << "My values: " << endl;

		cout << *this;
	}

	//Деструктор
	MyMatrix::~MyMatrix()
	{
		cout << "I'm destructor, for id: " << id << "\n";

		rows = 0;
		cols = 0;

		if (data)
		{
			delete[] data;
		}		
	}

	//Метод получения кол-ва строк
	int MyMatrix::getRows()const
	{
		return rows;
	}

	//Метод вставки кол-ва строк
	void MyMatrix::setRows(int _in)
	{
		rows = _in;
	}

	//Метод получения кол-ва колонок
	int MyMatrix::getCols()const
	{
		return cols;
	}

	//Метод вставки кол-ва колонок
	void MyMatrix::setCols(int _in)
	{
		cols = _in;
	}

	//Метод получения адреса на 1 элемент
	double* MyMatrix::getMatrix()const
	{
		return data;
	}

	//Метод вставки адреса на 1 элемент
	void MyMatrix::setMatrix(double* _in)
	{
		data = _in;
	}

	//Метод получения максимального элемента матрицы
	double MyMatrix::max()const
	{
		double myMax = numeric_limits<double>::min();
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (myMax < data[i*cols+j])
				{
					myMax = data[i*cols + j];
				}
			}
		}
		return myMax;
	}

	//Метод получения минимального элемента матрицы
	double MyMatrix::min()const
	{
		double myMin = numeric_limits<double>::max();
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (myMin > data[i*cols + j])
				{
					myMin = data[i*cols + j];
				}
			}
		}
		return myMin;
	}

	//Метод проверки возможности перемножения двух матриц
	bool MyMatrix::checkMul(MyMatrix& _in)const
	{
		return (cols == _in.getRows());
	}

	//Метод проверки возможности сложения двух матриц
	bool MyMatrix::checkAdd(MyMatrix& _in)const
	{
		return (rows == _in.getRows()) && (cols == _in.getCols());
	}

	//Переопределение оператора []
	double MyMatrix::Row::operator[](int _index)
	{
		if ((_index > maxCols) || (_index < 0))
		{
			throw logic_error{"Class MyMatrix, column index exceeds row size" + to_string(id)};
		}
		return row[_index];
	}

	MyMatrix::Row MyMatrix::operator[](int _index)
	{
		if ((_index > cols) || (_index < 0))
		{
			throw logic_error{"Class MyMatrix, row index exceeds cols size for id" + to_string(id)};
		}
		MyMatrix::Row pad;
		pad.row = &data[_index*cols];
		pad.maxCols = cols;
		pad.id = id;
		return pad;
	}

	const MyMatrix::Row MyMatrix::operator[](int _index)const
	{
		if ((_index > cols) || (_index < 0))
		{
			throw logic_error{"Class MyMatrix, row index exceeds cols size" + to_string(id)};
		}

		MyMatrix::Row pad;
		pad.row = &data[_index*cols];
		pad.maxCols = cols;
		pad.id = id;
		return pad;
	}

	//Переопределение оператора <<
	ostream& operator<<(ostream& os, const MyMatrix& _mat)
	{
		for (int i = 0; i < _mat.rows; i++)
		{
			os << endl;
			for (int j = 0; j < _mat.cols; j++)
			{
				os << setw(6) << fixed << setprecision(3) << _mat.data[i*_mat.cols+j] << " ";
			}
		}
		os << endl << endl;
		return os;
	}

	//Оператор перемещния
	MyMatrix& MyMatrix::operator=(MyMatrix&& _object)
	{
		if (this != &_object)
		{
			int bufOne = _object.rows;
			_object.rows = rows;
			rows = bufOne;

			bufOne = _object.cols;
			_object.cols = cols;
			cols = bufOne;

			double* bufTwo = _object.getMatrix();
			_object.setMatrix(data);
			data = bufTwo;
		}
		
		return *this;
	}

	//Переопределение оператора =
	MyMatrix& MyMatrix::operator=(const MyMatrix& _object)
	{
		if (!((rows == _object.getRows()) && (cols == _object.getCols())))
		{
			delete[] data;
			createMatrix(_object.getRows(), _object.getCols(), _object.data);

			return *this;
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i*cols + j] = _object.data[i*cols + j];
			}
		}
				
		return *this;
	}

	//Переопределение оператора +=
	MyMatrix& MyMatrix::operator+=(MyMatrix& _object)
	{
		if (!checkAdd(_object))
		{
			throw logic_error{"Class MyMatrix, objects are not compatible for addition for id" + to_string(id)};
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i*cols + j] += _object[i][j];
			}
		}

		return *this;
	}

	//Переопределение оператора -=
	MyMatrix& MyMatrix::operator-=(MyMatrix& _object)
	{
		if (!checkAdd(_object))
		{
			throw logic_error{"Class MyMatrix, objects are not compatible for subtraction for id" + to_string(id)};
		}

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i*cols + j] -= _object[i][j];
			}
		}

		return *this;
	}

	//Переопределение оператора *=
	MyMatrix& MyMatrix::operator*=(MyMatrix& _object)
	{				
		if (!checkMul(_object))
		{
			throw logic_error{"Class MyMatrix, objects are not compatible for multiplication for id" + to_string(id)};
		}

		double* newData = new double[rows*_object.getCols()];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < _object.getCols(); j++)
			{
				newData[i*_object.getCols() + j] = 0;
				for (int k = 0; k < cols; k++)
				{
					newData[i*_object.getCols() + j] += (data[i*cols + k] * _object[k][j]);
				}
			}
		}

		delete[] data;

		data = newData;

		cols = _object.getCols();

		return *this;
	}

	MyMatrix& MyMatrix::operator*=(const double right)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i*cols+j] *= right;
			}
		}
		return *this;
	}

	//Вспомогательный метод на заполнение матрицы данными
	void MyMatrix::createMatrix(int _rows, int _cols, const double* _data)
	{
		rows = _rows;
		cols = _cols;
		data = new double [rows*cols];
		if (!_data)
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					data[i*cols+j] = (j / (i + 1.0));
				}
			}
		}
		else
		{
			for (int i = 0; i < rows; i++)
			{
				for (int j = 0; j < cols; j++)
				{
					data[i*cols+j] = _data[i*j+j];
				}
			}
		}
	}

	//Переопределение оператора +
	MyMatrix operator+(MyMatrix& left, MyMatrix& right)
	{
		if (!left.checkAdd(right))
		{
			throw logic_error("Class MyMatrix, objects are not compatible");
		}

		MyMatrix Res(left);
		Res += right;
		return Res;
	}

	//Переопределение оператора -
	MyMatrix operator-(MyMatrix& left, MyMatrix& right)
	{
		if (!left.checkAdd(right))
		{
			throw logic_error("Class MyMatrix, objects are not compatible for subtraction");
		}

		MyMatrix Res(left);
		Res -= right;
		return Res;
	}

	//Переопределение оператора *
	MyMatrix operator*(MyMatrix& left, MyMatrix& right)
	{
		if (!left.checkMul(right))
		{
			throw logic_error("Class MyMatrix, objects are not compatible for multiplication");
		}

		MyMatrix Res(left);
		Res *= right;
		return Res;
	}

	//Переопределение оператора * на скаляр
	MyMatrix operator*(MyMatrix& left, double right)
	{
		MyMatrix Res(left);
		Res *= right;
		return Res;
	}
}
