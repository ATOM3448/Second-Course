#ifndef myvector_h
#define myvector_h

namespace myNameSpaces
{
	class MyMatrix
	{
	public:
		//1 �����������(����������/������������� � ��������� ���������, ������������)(�� ���������)
		explicit MyMatrix(int sizeInStrings = 0, int sizeInCollums = 0, double** data = NULL);

		//2 �����������(�����������)
		MyMatrix(const MyMatrix& early);

		//����������
		~MyMatrix();

		//����� ��������� ���-�� �����
		int getSizeInStrings()const;

		//����� ��������� ���-�� �������
		int getSizeInCollums()const;

		//����� ��������� ������ �� 1 �������
		double** getMatrix()const;

		//����� ��������� ������������� �������� �������
		double getMax()const;

		//����� ��������� ������������ �������� �������
		double getMin()const;

		//����� �������� ����������� ������������ ���� ������
		bool iCompatibleForMultiplication(MyMatrix& secondMat)const;

		//����� �������� ����������� �������� ���� ������
		bool iCompatibleForAdd(MyMatrix& secondMat)const;

		//��������������� ��������� []
		double* operator[](int index);

		//��������������� ��������� <<
		friend std::ostream& operator<<(std::ostream& os, const MyMatrix& mat);

		//��������������� ��������� =
		MyMatrix& operator=(const MyMatrix& right);

		//��������������� ��������� +=
		MyMatrix& operator+=(MyMatrix& right);

		//��������������� ��������� -=
		MyMatrix& operator-=(MyMatrix& right);

		//��������������� ��������� *=
		MyMatrix& operator*=(MyMatrix& right);

		MyMatrix& operator*=(const double right);

	private:
		//�������� ����������
		double** myData;
		int mySizeInStrings;
		int mySizeInCollums;
		const int id;
		static int newID;

		//��������������� ����� �� ���������� ������� �������
		void createMatrix(int sizeInStrings, int sizeInCollums, double** data = NULL);

		//��������������� ����� �� ����� �������
		void matrixOut();
	};

	//��������������� ��������� +
	MyMatrix operator+(MyMatrix& left, MyMatrix& right);

	//��������������� ��������� -
	MyMatrix operator-(MyMatrix& left, MyMatrix& right);

	//��������������� ��������� *
	MyMatrix operator*(MyMatrix& left, MyMatrix& right);

	//��������������� ��������� * �� ������
	MyMatrix operator*(MyMatrix& left, int right);
}
#endif