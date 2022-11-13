#ifndef myvector_h
#define myvector_h

namespace myNameSpaces
{

	class MyMatrix
	{
	public:
		//1 �����������(������������� � ��������� ���������, ������������)(�� ���������)
		explicit MyMatrix(unsigned int _rows = 0, unsigned int _cols = 0, double* _data = NULL);

		//2 �����������(�����������)
		MyMatrix(const MyMatrix& _early);

		//3 �����������(���������� � ��������� ���������, ������������)
		MyMatrix(unsigned int _size, double* _data);

		//4 �����������(swap)
		MyMatrix(MyMatrix&& _other);

		//����������
		~MyMatrix();

		//����� ��������� ���-�� �����
		int getRows()const;

		//����� ������� ���-�� �����
		void setRows(int _in);

		//����� ��������� ���-�� �������
		int getCols()const;

		//����� ������� ���-�� �������
		void setCols(int _in);

		//����� ��������� ������ �� 1 �������
		double* getMatrix()const;

		//����� ������� ������ �� 1 �������
		void setMatrix(double* _in);

		//����� ��������� ������������� �������� �������
		double max()const;

		//����� ��������� ������������ �������� �������
		double min()const;

		//����� �������� ����������� ������������ ���� ������
		bool checkMul(MyMatrix& _in)const;

		//����� �������� ����������� �������� ���� ������
		bool checkAdd(MyMatrix& _in)const;

		//��������������� ��������� []
		class adjacentClass
		{
		public:
			double* row;
			int maxCols;
			double operator[](int _index);
		};

		adjacentClass operator[](int _index);

		//��������������� ��������� <<
		friend std::ostream& operator<<(std::ostream& _os, const MyMatrix& _mat);

		//�������� �����������
		MyMatrix& operator=(MyMatrix&& _object);

		//��������������� ��������� =
		MyMatrix& operator=(const MyMatrix& _object);

		//��������������� ��������� +=
		MyMatrix& operator+=(MyMatrix& _object);

		//��������������� ��������� -=
		MyMatrix& operator-=(MyMatrix& _object);

		//��������������� ��������� *=
		MyMatrix& operator*=(MyMatrix& _object);

		MyMatrix& operator*=(const double _num);

	private:
		//�������� ����������
		double* data;
		int rows;
		int cols;
		const int id;
		static int newID;

		//��������������� ����� �� ���������� ������� �������
		void createMatrix(int _rows, int _cols, double* _data = NULL);
	};

	//��������������� ��������� +
	MyMatrix operator+(MyMatrix& left, MyMatrix& right);

	//��������������� ��������� -
	MyMatrix operator-(MyMatrix& left, MyMatrix& right);

	//��������������� ��������� *
	MyMatrix operator*(MyMatrix& left, MyMatrix& right);

	//��������������� ��������� * �� ������
	MyMatrix operator*(MyMatrix& left, double right);
}
#endif