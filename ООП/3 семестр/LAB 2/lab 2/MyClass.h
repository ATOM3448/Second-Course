#ifndef myvector_h
#define myvector_h

namespace myNameSpaces
{

	class MyMatrix
	{
	public:
		//1 Конструктор(прямоугольной с заданными размерами, компонентами)(по умолчанию)
		explicit MyMatrix(unsigned int _rows = 0, unsigned int _cols = 0, const double* _data = nullptr);

		//2 Конструктор(копирование)
		MyMatrix(const MyMatrix& _early);

		//3 Конструктор(квадратной с заданными размерами, компонентами)
		MyMatrix(unsigned int _size,const double* _data);

		//4 Конструктор(swap)
		MyMatrix(MyMatrix&& _other);

		//Деструктор
		~MyMatrix();

		int getID()const;

		//Метод получения кол-ва строк
		int getRows()const;

		//Метод вставки кол-ва строк
		void setRows(int _in);

		//Метод получения кол-ва колонок
		int getCols()const;

		//Метод вставки кол-ва колонок
		void setCols(int _in);

		//Метод получения адреса на 1 элемент
		double* getMatrix()const;

		//Метод вставки адреса на 1 элемент
		void setMatrix(double* _in);

		//Метод получения максимального элемента матрицы
		double max()const;

		//Метод получения минимального элемента матрицы
		double min()const;

		//Метод проверки возможности перемножения двух матриц
		bool checkMul(MyMatrix& _in)const;

		//Метод проверки возможности сложения двух матриц
		bool checkAdd(MyMatrix& _in)const;

		//Переопределение оператора []
		class Row
		{
		public:
			double* row;
			int maxCols;
			double operator[](int _index);
		};

		Row operator[](int _index);
		const Row operator[](int _index)const;

		//Переопределение оператора <<
		friend std::ostream& operator<<(std::ostream& _os, const MyMatrix& _mat);

		//Оператор перемещения
		MyMatrix& operator=(MyMatrix&& _object);

		//Переопределение оператора =
		MyMatrix& operator=(const MyMatrix& _object);

		//Переопределение оператора +=
		MyMatrix& operator+=(MyMatrix& _object);

		//Переопределение оператора -=
		MyMatrix& operator-=(MyMatrix& _object);

		//Переопределение оператора *=
		MyMatrix& operator*=(MyMatrix& _object);

		MyMatrix& operator*=(const double _num);

	private:
		//Основные переменные
		double* data;
		int rows;
		int cols;
		const int id;
		static int newID;

		//Вспомогательный метод на заполнение матрицы данными
		void createMatrix(int _rows, int _cols, const double* _data = nullptr);
	};

	//Переопределение оператора +
	MyMatrix operator+(MyMatrix& left, MyMatrix& right);

	//Переопределение оператора -
	MyMatrix operator-(MyMatrix& left, MyMatrix& right);

	//Переопределение оператора *
	MyMatrix operator*(MyMatrix& left, MyMatrix& right);

	//Переопределение оператора * на скаляр
	MyMatrix operator*(MyMatrix& left, double right);
}
#endif