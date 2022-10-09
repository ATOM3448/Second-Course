#include <iostream>
#include <iomanip>
#include "MyClass.h"
using namespace std;


namespace myNameSpaces
{
	int MyMatrix::newID = 0;
	//1 Конструктор(квадратной/прямоугольной с заданными размерами, компонентами)(по умолчанию)
	MyMatrix::MyMatrix(int sizeInStrings, int sizeInCollums, double** data) :id{ newID++ }
	{
		cout << "\nI'm constructor #1, for id: " << id << endl;

		if (!sizeInStrings)
		{
			createMatrix(5, 5);
		}
		else
		{
			if (sizeInCollums)
			{
				createMatrix(sizeInStrings, sizeInCollums, data);
			}
			else
			{
				createMatrix(sizeInStrings, sizeInStrings, data);
			}
			if (data)
			{
				for (int i = 0; i < mySizeInStrings; i++)
				{
					delete[] data[i];
				}
				delete[] data;
			}
		}

		cout << "My values: " << endl;

		matrixOut();
	}

	//2 Конструктор(копирование)
	MyMatrix::MyMatrix(const MyMatrix& early) :id{ newID++ }
	{
		cout << "I'm construcor #2, for id: " << id << "\n";

		mySizeInStrings = early.mySizeInStrings;
		mySizeInCollums = early.mySizeInCollums;

		myData = new double* [mySizeInStrings];
		for (int i = 0; i < mySizeInStrings; i++)
		{
			myData[i] = new double[mySizeInCollums];
			for (int j = 0; j < mySizeInCollums; j++)
			{
				myData[i][j] = early.myData[i][j];
			}
		}

		cout << "My values: " << endl;

		matrixOut();
	}

	//Деструктор
	MyMatrix::~MyMatrix()
	{
		cout << "I'm destructor, for id: " << id << "\n";

		mySizeInStrings = 0;
		mySizeInCollums = 0;

		for (int i = 0; i < mySizeInStrings; i++)
		{
			delete[] myData[i];
		}
		delete[] myData;
	}

	//Метод получения кол-ва строк
	int MyMatrix::getSizeInStrings()const
	{
		return mySizeInStrings;
	}

	//Метод получения кол-ва колонок
	int MyMatrix::getSizeInCollums()const
	{
		return mySizeInCollums;
	}

	//Метод получения адреса на 1 элемент
	double** MyMatrix::getMatrix()const
	{
		return myData;
	}

	//Метод получения максимального элемента матрицы
	double MyMatrix::getMax()const
	{
		double myMax = numeric_limits<double>::min();
		for (int i = 0; i < mySizeInStrings; i++)
		{
			for (int j = 0; j < mySizeInCollums; j++)
			{
				if (myMax < myData[i][j])
				{
					myMax = myData[i][j];
				}
			}
		}
		return myMax;
	}

	//Метод получения минимального элемента матрицы
	double MyMatrix::getMin()const
	{
		double myMin = numeric_limits<double>::max();
		for (int i = 0; i < mySizeInStrings; i++)
		{
			for (int j = 0; j < mySizeInCollums; j++)
			{
				if (myMin > myData[i][j])
				{
					myMin = myData[i][j];
				}
			}
		}
		return myMin;
	}

	//Метод проверки возможности перемножения двух матриц
	bool MyMatrix::iCompatibleForMultiplication(MyMatrix& secondMat)const
	{
		return (mySizeInCollums == secondMat.getSizeInStrings());
	}

	//Метод проверки возможности сложения двух матриц
	bool MyMatrix::iCompatibleForAdd(MyMatrix& secondMat)const
	{
		return (mySizeInStrings == secondMat.getSizeInStrings()) && (mySizeInCollums == secondMat.getSizeInCollums());
	}

	//Переопределение оператора []
	double* MyMatrix::operator[](int index)
	{
		return myData[index];
	}

	//Переопределение оператора <<
	ostream& operator<<(ostream& os, const MyMatrix& mat)
	{
		for (int i = 0; i < mat.mySizeInStrings; i++)
		{
			os << endl;
			for (int j = 0; j < mat.mySizeInCollums; j++)
			{
				os << setw(6) << fixed << setprecision(3) << mat.myData[i][j] << " ";
			}
		}
		os << endl << endl;
		return os;
	}
	
	//Переопределение оператора =
	MyMatrix& MyMatrix::operator=(const MyMatrix& right)
	{
		for (int i = 0; i < mySizeInStrings; i++)
		{
			delete[] myData[i];
		}
		delete[] myData;

		createMatrix(right.getSizeInStrings(), right.getSizeInCollums(), right.myData);
				
		return *this;
	}

	//Переопределение оператора +=
	MyMatrix& MyMatrix::operator+=(MyMatrix& right)
	{
		if (iCompatibleForAdd(right))
		{
			for (int i = 0; i < mySizeInStrings; i++)
			{
				for (int j = 0; j < mySizeInCollums; j++)
				{
					myData[i][j] += right[i][j];
				}
			}
		}

		return *this;
	}

	//Переопределение оператора -=
	MyMatrix& MyMatrix::operator-=(MyMatrix& right)
	{
		if (iCompatibleForAdd(right))
		{
			for (int i = 0; i < mySizeInStrings; i++)
			{
				for (int j = 0; j < mySizeInCollums; j++)
				{
					myData[i][j] -= right[i][j];
				}
			}
		}

		return *this;
	}

	//Переопределение оператора *=
	MyMatrix& MyMatrix::operator*=(MyMatrix& right)
	{				
		if (iCompatibleForMultiplication(right))
		{
			double** newData = new double*[mySizeInStrings];
			for (int i = 0; i < mySizeInStrings; i++)
			{
				newData[i] = new double[right.getSizeInCollums()];
				for (int j = 0; j < right.getSizeInCollums(); j++)
				{
					newData[i][j] = 0;
					for (int k = 0; k < mySizeInCollums; k++)
					{
						newData[i][j] += (myData[i][k] * right[k][j]);
					}
				}
			}

			for (int i = 0; i < mySizeInStrings; i++)
			{
				delete[] myData[i];
			}
			delete[] myData;

			myData = newData;
		}

		mySizeInCollums = right.getSizeInCollums();

		return *this;
	}

	MyMatrix& MyMatrix::operator*=(const double right)
	{
		for (int i = 0; i < mySizeInStrings; i++)
		{
			for (int j = 0; j < mySizeInCollums; j++)
			{
				myData[i][j] *= right;
			}
		}
		return *this;
	}

	//Вспомогательный метод на заполнение матрицы данными
	void MyMatrix::createMatrix(int sizeInStrings, int sizeInCollums, double** data)
	{
		mySizeInStrings = sizeInStrings;
		mySizeInCollums = sizeInCollums;
		myData = new double* [mySizeInStrings];
		if (!data)
		{
			for (int i = 0; i < mySizeInStrings; i++)
			{
				myData[i] = new double[mySizeInCollums];
				for (int j = 0; j < mySizeInCollums; j++)
				{
					myData[i][j] = (j / (i + 1.0));
				}
			}
		}
		else
		{
			for (int i = 0; i < mySizeInStrings; i++)
			{
				myData[i] = new double[mySizeInCollums];
				for (int j = 0; j < mySizeInCollums; j++)
				{
					myData[i][j] = data[i][j];
				}
			}
		}
	}

	//Вспомогательный метод на вывод матрицы
	void MyMatrix::matrixOut()
	{
		for (int i = 0; i < mySizeInStrings; i++)
		{
			cout << endl;
			for (int j = 0; j < mySizeInCollums; j++)
			{
				cout << setw(6) << fixed << setprecision(3) << myData[i][j] << " ";
			}
		}
		cout << endl << endl;
	}

	//Переопределение оператора +
	MyMatrix operator+(MyMatrix& left, MyMatrix& right)
	{
		MyMatrix newMat(left);
		if (left.iCompatibleForAdd(right))
		{
			for (int i = 0; i < newMat.getSizeInStrings(); i++)
			{
				for (int j = 0; j < newMat.getSizeInCollums(); j++)
				{
					newMat[i][j] += right[i][j];
				}
			}
		}
		else
		{
			cout << "ERROR!!!";
			exit(EXIT_FAILURE);
		}
		return newMat;
	}

	//Переопределение оператора -
	MyMatrix operator-(MyMatrix& left, MyMatrix& right)
	{
		MyMatrix newMat(left);
		if (left.iCompatibleForAdd(right))
		{
			for (int i = 0; i < newMat.getSizeInStrings(); i++)
			{
				for (int j = 0; j < newMat.getSizeInCollums(); j++)
				{
					newMat[i][j] -= right[i][j];
				}
			}
		}
		else
		{
			cout << "ERROR!!!";
			exit(EXIT_FAILURE);
		}
		return newMat;
	}

	//Переопределение оператора *
	MyMatrix operator*(MyMatrix& left, MyMatrix& right)
	{
		MyMatrix newMat(left.getSizeInStrings(), right.getSizeInCollums());
		if (left.iCompatibleForMultiplication(right))
		{
			for (int i = 0; i < left.getSizeInStrings(); i++)
			{
				for (int j = 0; j < right.getSizeInCollums(); j++)
				{
					newMat[i][j] = 0;
					for (int k = 0; k < left.getSizeInCollums(); k++)
					{
						newMat[i][j] += (left[i][k] * right[k][j]);
					}
				}
			}
		}
		else
		{
			cout << "ERROR!!!";
			exit(EXIT_FAILURE);
		}
		return newMat;
	}

	//Переопределение оператора * на скаляр
	MyMatrix operator*(MyMatrix& left, int right)
	{
		MyMatrix newMat(left);
		for (int i = 0; i < newMat.getSizeInStrings(); i++)
		{
			for (int j = 0; j < newMat.getSizeInCollums(); j++)
			{
				newMat[i][j] *= right;
			}
		}
		return newMat;
	}
}