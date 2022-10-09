#include <iostream>
#include "MyClass.h"

using namespace std;
using namespace myNameSpaces;

//Функция ввода данных(если надо)(mode = 0 - квадратная матрица, mode = 1 - по заданым значениям)
double** inputFun(int* strings, int* collums, char mode = 0)
{
	int countStrings = 0;
	int countCollums = 0;

	double** userData;

	if (mode)
	{
		cout << "Count of strings: ";
	}
	else
	{
		cout << "Size: ";
	}

	cin >> countStrings;

	if (mode)
	{
		cout << "\nCount of collums: ";
		cin >> countCollums;
	}

	cout << "\nEnter values:\n";

	userData = new double* [countStrings];
	for (int i = 0; i < countStrings; i++)
	{
		if (mode)
		{
			userData[i] = new double[countCollums];
			for (int j = 0; j < countCollums; j++)
			{
				cin >> userData[i][j];
			}
			cout << endl;
		}
		else
		{
			userData[i] = new double[countStrings];
			for (int j = 0; j < countStrings; j++)
			{
				cin >> userData[i][j];
			}
			cout << endl;
		}
	}

	*strings = countStrings;
	if (mode)
	{
		*collums = countCollums;
	}
	else
	{
		*collums = countStrings;
	}

	return userData;
}

int main()
{
	int countOfStrings = 3;
	int countOfCollums = 3;

	double** data = new double*[countOfStrings];
	for (int i = 0; i < countOfStrings; i++)
	{
		data[i] = new double[countOfCollums];
		for (int j = 0; j < countOfCollums; j++)
		{
			data[i][j] = (1 + rand() % 100) + (1 / (1+rand() % 100));
		}
	}

	MyMatrix matOne(countOfStrings, countOfCollums, data);

	countOfStrings = 3;
	countOfCollums = 3;

	data = new double* [countOfStrings];
	for (int i = 0; i < countOfStrings; i++)
	{
		data[i] = new double[countOfCollums];
		for (int j = 0; j < countOfCollums; j++)
		{
			data[i][j] = (1 + rand() % 100) + (1 / (1 + rand() % 100));
		}
	}

	MyMatrix matTwo(countOfStrings, countOfCollums, data);

	MyMatrix matThree = matOne * 2;
	cout << matThree;

	system("pause");

	return 0;
}