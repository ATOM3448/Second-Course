#include <iostream>
#include <ctime>
#include <math.h>

#include "myvector.h"

using namespace myClasses;
using namespace std;

int main()
{
	setlocale(LC_ALL, "russian");

	//Создание векторов

	My_Vector vectorOne(5, 8, 2);

	cout << "X1: " << vectorOne.get_X() << "\n";
	cout << "Y1: " << vectorOne.get_Y() << "\n";
	cout << "Z1: " << vectorOne.get_Z() << "\n";

	std::cout << "\n";

	My_Vector vectorTwo(-5, -7, 8);

	cout << "X2: " << vectorTwo.get_X() << "\n";
	cout << "Y2: " << vectorTwo.get_Y() << "\n";
	cout << "Z2: " << vectorTwo.get_Z() << "\n" << "\n";

	//Вывод C1
	My_Vector C_one = sum(vectorOne, vectorTwo);
	cout << "X: " << C_one.get_X() << "\n";
	cout << "Y: " << C_one.get_Y() << "\n";
	cout << "Z: " << C_one.get_Z() << "\n" << "\n";

	//Вывод C2
	My_Vector C_two = sub(vectorOne, vectorTwo);
	cout << "X: " << C_two.get_X() << "\n";
	cout << "Y: " << C_two.get_Y() << "\n";
	cout << "Z: " << C_two.get_Z() << "\n" << "\n";

	//Вывод C3
	My_Vector C_three = multiplVect(vectorOne, vectorTwo);
	cout << "X: " << C_three.get_X() << "\n";
	cout << "Y: " << C_three.get_Y() << "\n";
	cout << "Z: " << C_three.get_Z() << "\n" << "\n";

	//Вывод единичного вектора
	My_Vector copyOfVO(vectorOne);
	copyOfVO.unitVect();
	cout << "unit X: " << copyOfVO.get_X() << "\n";
	cout << "unit Y: " << copyOfVO.get_Y() << "\n";
	cout << "unit Z: " << copyOfVO.get_Z() << "\n" << "\n";

	//Вывод скалярного произведения
	cout << "skalMult: " << multiplSkal(vectorOne, vectorTwo) << endl;

	//Вывод синуса
	cout << "Sin: " << mySin(vectorOne, vectorTwo) << endl;

	//Вывод косинуса
	cout << "Cos: " << myCos(vectorOne, vectorTwo) << endl;

	//Вывод угла
	cout << "Angle: " << myAngle(vectorOne, vectorTwo) << endl;

	cin.get();

	return 0;
}

