using System;
using System.IO;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class MyMatrix : IEnumerable, IFormattable, ICloneable
    {
        private double[] data;
        private uint row;
        private uint col;
        private static uint newID = 0;
        private uint id;

        public uint Row { get { return row; } private set { row = value; } }
        public uint Col { get { return col; } private set { col = value; } }

        public double[] Data { get { return data; } private set { data = value; } }

        //1 Конструктор по умолчанию/кастом
        public MyMatrix(uint _row = 3, uint _col = 3, double[] _data = null)
        {
            if ((_row == 0) || (_col == 0))
            {
                throw new ArgumentException("Количество строк и колонок должно быть отлично от 0");
            }

            if ((_data != null) && (_row*_col > _data.Length))
            {
                throw new ArgumentException("Данных не достаточно для полного заполнения матрицы");
            }

            if ((_data != null) && (_row*_col < _data.Length))
            {
                throw new ArgumentException("Выход за пределы размеров матрицы");
            }

            id = newID++;

            row = _row;
            col = _col;

            data = new double[row * col];

            if(_data != null)
            {
                _data.CopyTo(data, 0);
            }
            else
            {
                for (int i = 0; i < col * row; i++)
                {
                    data[i] = 0;
                }
            }
        }

        //2 Конструктор квадратной кастом
        public MyMatrix(uint _size, double[] _data) : this(_size, _size, _data)
        {
        }

        //3 Конструктор копирования
        public MyMatrix(MyMatrix _early) : this(_early.row, _early.col, _early.data)
        {
        }

        // Поиск обратной матрицы ортогонализацией
        public static MyMatrix Ortog_Inverse(MyMatrix _base)
        {
            uint n = _base.col;
            double[] dataInv = new double[n * n];

            double[] dataUnit = new double[n * n];
            for(int i = 0; i < n; i++)
            {
                dataUnit[i * n + i] = 1;
            }

            MyMatrix unit = new MyMatrix(n, n, dataUnit);

            for(uint i = 0; i < n; i++)
            {
                MySLAU iLineSLAU = new MySLAU(n, _base.data, unit.GetCollum(i));
                iLineSLAU.Orthogonalization();
                for(uint j = 0; j < n; j++)
                {
                    dataInv[j * n + i] = iLineSLAU.x[j,0];
                }
            }

            MyMatrix answ = new MyMatrix(n, n, dataInv);

            StreamWriter sw = new StreamWriter("D:/ЧМ/Lab2/Lab2/OUT.txt", true);

            sw.WriteLine(answ);

            MyMatrix E = _base * answ - unit;

            sw.WriteLine(E);
            sw.WriteLine("\n");

            double normE = 0;

            for (uint i = 0; i < E.Row; i++)
            {
                for (uint j = 0; j < E.Col; j++)
                {
                    normE += E[i, j] * E[i, j];
                }
            }

            normE = Math.Sqrt(normE);

            sw.WriteLine(normE);

            sw.Close();

            return answ;
        }

        //Поиск обратной матрицы простой итерацией
        public static MyMatrix Iter_Inverse(MyMatrix _base)
        {
            uint n = _base.col;
            double[] dataInv = new double[n * n];

            double[] dataUnit = new double[n * n];
            for (int i = 0; i < n; i++)
            {
                dataUnit[i * n + i] = 1;
            }

            MyMatrix unit = new MyMatrix(n, n, dataUnit);

            for (uint i = 0; i < n; i++)
            {
                MySLAU iLineSLAU = new MySLAU(n, _base.data, unit.GetCollum(i));
                iLineSLAU.Iterations();
                for (uint j = 0; j < n; j++)
                {
                    dataInv[j * n + i] = iLineSLAU.x[j, 0];
                }
            }

            MyMatrix answ = new MyMatrix(n, n, dataInv);

            StreamWriter sw = new StreamWriter("D:/ЧМ/Lab2/Lab2/OUT.txt", true);

            sw.WriteLine(answ);

            MyMatrix E = _base * answ - unit;

            sw.WriteLine(E);
            sw.WriteLine("\n");

            double normE = 0;

            for (uint i = 0; i < E.Row; i++)
            {
                for (uint j = 0; j < E.Col; j++)
                {
                    normE += E[i, j] * E[i, j];
                }
            }

            normE = Math.Sqrt(normE);

            sw.WriteLine(normE);

            sw.Close();

            return answ;
        }

        public double[] GetString(uint _num, uint end = 0)
        {
            double[] ai = new double[col];
            for (uint j = 0; j < col-end; j++)
            {
                ai[j] = data[_num * col + j];
            }

            return ai;
        }

        public double[] GetCollum(uint _num, uint end = 0)
        {
            double[] aj = new double[row];
            for (uint i = 0; i < row-end; i++)
            {
                aj[i] = data[i * col + _num];
            }

            return aj;
        }

        //Проверка умножения
        public bool CheckMul(MyMatrix _operand)
        {
            if (_operand == null)
            {
                throw new ArgumentException("Операнд не инициализрован");
            }

            if(col == _operand.row)
            {
                return true;
            }
            return false;
        }

        //Проверка сложения
        public bool CheckAdd(MyMatrix _operand)
        {
            if (_operand == null)
            {
                throw new ArgumentException("Операнд не инициализрован");
            }

            if ((col == _operand.col) && (row == _operand.row))
            {
                return true;
            }
            return false;
        }

        //Найти максимальный элемент матрицы
        public double Max()
        {
            return data.Max();
        }

        //Найти минимальный элемент матрицы
        public double Min()
        {
            return data.Min();
        }

        //Оператор умножения (матрица, матрица)
        public static MyMatrix operator*(MyMatrix _operand1, MyMatrix _operand2)
        {
            if(!_operand1.CheckMul(_operand2))
            {
                throw new ArgumentException("Данные матрицы нельзя перемножать");
            }

            double[] newData = new double[_operand1.row * _operand2.col];
            for (int i = 0; i < _operand1.row; i++)
            {
                for (int j = 0; j < _operand2.col; j++)
                {
                    newData[i * _operand2.col + j] = 0;
                    for (int k = 0; k < _operand1.col; k++)
                    {
                        newData[i * _operand2.col + j] += (_operand1.data[i * _operand1.col + k] * _operand2.data[k * _operand2.col + j]);
                    }
                }
            }

            MyMatrix toOut = new MyMatrix(_operand1.row, _operand2.col, newData);

            return toOut;
        }

        //Оператор умножения (матрица, скаляр)
        public static MyMatrix operator*(MyMatrix _operand1, double _operand2)
        {
            if (_operand2 == null)
            {
                throw new ArgumentException("Второй операнд не инициализрован");
            }

            double[] newData = new double[_operand1.row * _operand1.col];

            _operand1.data.CopyTo(newData, 0);

            for(int i = 0; i < (_operand1.col * _operand1.row); i++)
            {
                newData[i] *= _operand2;
            }

            MyMatrix toOut = new MyMatrix(_operand1.row, _operand1.col, newData);

            return toOut;
        }

        //Оператор сложения (матрица, матрица)
        public static MyMatrix operator+(MyMatrix _operand1, MyMatrix _operand2)
        {
            if(!_operand1.CheckAdd(_operand2))
            {
                throw new ArgumentException("Данные матрицы нельзя складывать");
            }

            double[] newData = new double[_operand1.row * _operand1.col];

            _operand1.data.CopyTo(newData, 0);

            for (int i = 0; i < _operand1.row * _operand1.col; i++)
            {
                newData[i] += _operand2.data[i];
            }

            MyMatrix toOut = new MyMatrix(_operand1.row, _operand1.col, newData);

            return toOut;
        }

        //Оператор вычитания (матрица, матрица)
        public static MyMatrix operator -(MyMatrix _operand1, MyMatrix _operand2)
        {
            if (!_operand1.CheckAdd(_operand2))
            {
                throw new ArgumentException("Данные матрицы нельзя вычитать");
            }

            double[] newData = new double[_operand1.row * _operand1.col];

            _operand1.data.CopyTo(newData, 0);

            for (int i = 0; i < _operand1.row * _operand1.col; i++)
            {
                newData[i] -= _operand2.data[i];
            }

            MyMatrix toOut = new MyMatrix(_operand1.row, _operand1.col, newData);

            return toOut;
        }

        //Индексатор
        public double this[uint i, uint j]
        {
            get { return data[i * col + j]; }
            set { data[i * col + j] = value; }
        }

        //Перевод в строку
        public override string ToString()
        {
            string toOut = "";
            for(int i = 0; i < row; i++)
            {
                for(int j = 0; j < col; j++)
                {
                    toOut += data[i * col + j].ToString();
                    toOut += " ";
                }
                toOut += "\n";
            }
            return toOut;
        }

        //Интерфейс клонирования
        object ICloneable.Clone()
        {
            return Clone();
        }

        public MyMatrix Clone()
        {
            MyMatrix toOut = new MyMatrix(this.row, this.col, this.data);

            return toOut;
        }

        //Интерфейс форматирования
        string IFormattable.ToString(string format, IFormatProvider formatProvider)
        {
            string toOut = "";
            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    toOut += data[i * col + j].ToString();
                    toOut += " ";
                }
                toOut += "\n";
            }
            return toOut;
        }

        //Интерфейс перечисления
        IEnumerator IEnumerable.GetEnumerator()
        {
            return data.GetEnumerator();
        }
    };
}
