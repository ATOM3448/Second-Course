#ifndef myvector_h
#define myvector_h

namespace myClasses
{
	class My_Vector
	{
	private:
		double X, Y, Z;
		static int newID;
		const int id;
	public:
		//Конструктор основной
		explicit My_Vector(double _x, double _y, double _z);

		//Конструктор копирования
		My_Vector(const My_Vector& early);

		//Деконструктор
		~My_Vector();

		int getId();

		//Чтение
		double get_X()const;
		double get_Y()const;
		double get_Z()const;

		//Запись
		void set_X(double _x);
		void set_Y(double _y);
		void set_Z(double _z);

		//Вычисление модуля вектора
		double mod();

		//Умножение вектора на скаляр
		void multiplication(double _x);

		//Копирование вектора
		void copy(My_Vector& early);

		//Нормировка
		void unitVect();
	};
	My_Vector sum(My_Vector& vectorOne, My_Vector& vectorTwo);

	My_Vector sub(My_Vector& vectorOne, My_Vector& vectorTwo);

	My_Vector multiplVect(My_Vector& vectorOne, My_Vector& vectorTwo);

	double multiplSkal(My_Vector& vectorOne, My_Vector& vectorTwo);

	double mySin(My_Vector& vectorOne, My_Vector& vectorTwo);

	double myCos(My_Vector& vectorOne, My_Vector& vectorTwo);

	double myAngle(My_Vector& vectorOne, My_Vector& vectorTwo);
}

#endif