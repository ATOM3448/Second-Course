#include <iostream>
#include "MyClass.h"

using namespace std;
using namespace myNameSpaces;

int main()
{
	try
	{
		int rows = 3;
		int cols = 3;

		double* data = new double[rows*cols];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i*cols + j] = (1 + rand() % 10) + (1 / (1 + rand() % 100));
			}
		}

		MyMatrix matOne(rows, cols, data);

		rows = 3;
		cols = 3;

		data = new double[rows*cols];
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				data[i*cols + j] = (1 + rand() % 10) + (1 / (1 + rand() % 100));
			}
		}

		MyMatrix matTwo(rows, cols, data);

		//------------
		cout << matOne[0][0] << '\n';

		matOne = matTwo;
		cout << "----Assignment Operator:\n" << matOne;

		matOne += matTwo;
		cout << "----Assignment operator with addition:\n" << matOne;

		matOne -= matTwo;
		cout << "----Assignment operator with subtraction:\n" << matOne;

		matOne *= matTwo;
		cout << "----Assignment operator with multiplication:\n" << matOne;

		matOne *= 2;
		cout << "----Assignment operator multiplied by a scalar:\n" << matOne;

		cout << "----Addition Operator:\n";
		cout << (matOne + matTwo);

		cout << "\n----Subtraction operator:\n";
		cout << (matOne - matTwo);

		cout << "\n----Multiplication operator:\n";
		cout << (matOne * matTwo);

		cout << "\n----Multiplication operator by scalar:\n";
		cout << (matOne * 2);

		cout << "\n----Swap:\n";
		matOne = move(matTwo);
		cout << matOne << "\n\n" << matTwo;
		//------------

		system("pause");
	}
	catch(exception)
	{
		cout << "Erorr";
	}

	return 0;
}