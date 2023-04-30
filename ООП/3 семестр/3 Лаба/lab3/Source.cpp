#include <iostream>
#include "NewMatrix.h"
#include "NewVector.h"
#include "MyBaseClass.h"

using namespace std;
using namespace myTask;

int main()
{
	double data[] = { 1, 2, 3, 6, 7, 8, 1, 2, 3 };

	try
	{
		NewMatrix mat1(3, 3, &data[0]);

		cout << endl << mat1 << endl;

		NewMatrix mat2;

		cout << endl << mat2 << endl;

		cout << endl << mat1 * mat2 << endl;

		cout << endl << mat1 * 5 << endl;

		cout << endl << mat1 - mat2 << endl;

		cout << endl << mat1 + mat2 << endl;
	}
	catch (logic_error& e)
	{
		cout << "logic error";
	}

	system("pause");

	return 0;
}