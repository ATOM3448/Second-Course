#ifndef myvector_h
#define myvector_h

namespace myNameSpaces
{
	class MyMatrix
	{
	public:
		//1 Конструктор(квадратной/прямоугольной с заданными размерами, компонентами)(по умолчанию)
		explicit MyMatrix(int sizeInStrings = 0, int sizeInCollums = 0, double** data = NULL);

		//2 Конструктор(копирование)
		MyMatrix(const MyMatrix& early);

		//Деструктор
		~MyMatrix();

		//Метод получения кол-ва строк
		int getSizeInStrings()const;

		//Метод получения кол-ва колонок
		int getSizeInCollums()const;

		//Метод получения адреса на 1 элемент
		double** getMatrix()const;

		//Метод получения максимального элемента матрицы
		double getMax()const;

		//Метод получения минимального элемента матрицы
		double getMin()const;

		//Метод проверки возможности перемножения двух матриц
		bool iCompatibleForMultiplication(MyMatrix& secondMat)const;

		//Метод проверки возможности сложения двух матриц
		bool iCompatibleForAdd(MyMatrix& secondMat)const;

		//Переопределение оператора []
		double* operator[](int index);

		//Переопределение оператора <<
		friend std::ostream& operator<<(std::ostream& os, const MyMatrix& mat);

		//Переопределение оператора =
		MyMatrix& operator=(const MyMatrix& right);

		//Переопределение оператора +=
		MyMatrix& operator+=(MyMatrix& right);

		//Переопределение оператора -=
		MyMatrix& operator-=(MyMatrix& right);

		//Переопределение оператора *=
		MyMatrix& operator*=(MyMatrix& right);

		MyMatrix& operator*=(const double right);

	private:
		//Основные переменные
		double** myData;
		int mySizeInStrings;
		int mySizeInCollums;
		const int id;
		static int newID;

		//Вспомогательный метод на заполнение матрицы данными
		void createMatrix(int sizeInStrings, int sizeInCollums, double** data = NULL);

		//Вспомогательный метод на вывод матрицы
		void matrixOut();
	};

	//Переопределение оператора +
	MyMatrix operator+(MyMatrix& left, MyMatrix& right);

	//Переопределение оператора -
	MyMatrix operator-(MyMatrix& left, MyMatrix& right);

	//Переопределение оператора *
	MyMatrix operator*(MyMatrix& left, MyMatrix& right);

	//Переопределение оператора * на скаляр
	MyMatrix operator*(MyMatrix& left, int right);
}
#endif