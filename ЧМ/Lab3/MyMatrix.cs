using System;
using System.Collections;
using System.Data;
using System.IO;
using System.Linq;
using System.Net.WebSockets;
using PolStrLib;

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

        //Собственные числа
        public double[,] EigenValues(in StreamWriter _sw = null)
        {
            double[] values = new double[row];

            MyMatrix p = this.Frob();

            if (_sw != null)
            {
                _sw.WriteLine("Матрица Фробениуса:");

                _sw.WriteLine(p);
            }

            for (uint i = 0; i < row; i++)
                values[i] = p[0, i];

            return PolinRoot(values);
        }

        public double CheckEigen(double _eigen)
        {
            MyMatrix tempMat = this - this.GetUnit() * _eigen;

            return tempMat.Det();
        }

        public MyMatrix CheckEigenVect(MyMatrix _vect, double _eigen)
        {
            return (this * _vect) - (_vect * _eigen);
        }

        public double Det()
        {
            MyMatrix copy = this.Clone();

            double det = 1;

            for (uint i = 0; i < row; i++)
            {
                double cof = copy[i, i];

                det *= cof;

                for (uint j = i; j < row; j++)
                    copy[i, j] /= cof;

                for(uint j = i+1; j < row; j++)
                {
                    cof = copy[j, i];
                    for(uint k = i; k < row; k++)
                    {
                        copy[j, k] -= cof * copy[i, k];
                    }
                }
            }

            return det;
        }

        //Решение полинома
        private static double[,] PolinRoot(double[] _values, double _start = -10, double _end = 10,double _disp = 0.001, double _step = 0.0001)
        {
            string polinom;

            string fx = GetPolin(_values);

            PolStr.StrToPolStr(fx,out polinom, 0);

            double[,] answ = new double[_values.Count(), 2];

            bool wasFound = false;

            double x0 = 0;

            double f0 = PolStr.EvalPolStr(polinom, x0, 0);
            f0 = _values.Count() % 2 == 0 ? f0 : -f0;
            double f1 = f0;

            uint counter = 0;

            for(double x1 = _start; (counter < _values.Count()) || (x1 < _end); x1 += _step)
            {
                f0 = f1;
                f1 = PolStr.EvalPolStr(polinom, x1, 0);
                f1 = _values.Count() % 2 == 0 ? f1 : -f1;

                if ((Math.Abs(f1) <= _disp) && (Math.Abs(f1) < Math.Abs(f0)))
                {
                    x0 = x1;
                    wasFound = true;
                    continue;
                }

                if(wasFound || ((f0 * f1) < 0))
                {
                    wasFound = false;

                    uint multiplicity = 1;

                    answ[counter, 0] = x0;

                    double tempDisp = _disp;

                    while(Math.Abs(PolStr.EvalPolStr(polinom, x0, multiplicity)) < tempDisp)
                    {
                        ++multiplicity;

                        tempDisp *= 10;
                    }

                    for(uint i = 0; i < (multiplicity-1); i++)
                    {
                        answ[counter, 1] = multiplicity;
                        
                        answ[++counter, 0] = x0;
                    }
                    answ[counter++, 1] = multiplicity;
                }
            }

            if (counter < _values.Count())
                throw new ArgumentOutOfRangeException("Какой либо из параметров препятсвует нахождению корней");

            return answ;
        }

        /*private static double[,] PolinRoot(double[] _values, double _a = -100, double _b = 100, double _disp = 0.001, double _step = 1)
        {
            string polinom;

            string fx = GetPolin(_values);

            PolStr.StrToPolStr(fx, out polinom, 0);

            double[,] answ = new double[_values.Count(), 2];

            uint counter = 0;

            do
            {
                double[] buf = Newton(polinom, ref _a, ref _b, _disp);
                _b -= _step;

                double x = buf[0];
                double f = buf[1];

                uint multiplicity = 1;

                answ[counter, 0] = x;

                double tempDisp = _disp;

                while (Math.Abs(PolStr.EvalPolStr(polinom, x, multiplicity)) < tempDisp)
                {
                   ++multiplicity;

                   tempDisp *= 10;
                }

                for (uint i = 0; i < (multiplicity - 1); i++)
                {
                   answ[counter, 1] = multiplicity;

                   answ[++counter, 0] = x;
                }
                answ[counter++, 1] = multiplicity;

            } while (counter < _values.Count());

            return answ;
        }*/

        /*private static double[] Newton(string _polinom, ref double _a, ref double _b, double _disp)
        {
            double a = _a;
            double b = _b;

            double[] answ = new double[2];

            double fxA = PolStr.EvalPolStr(_polinom, a, 0);
            double fxB = PolStr.EvalPolStr(_polinom, b, 0);

            double x0;

            double dispFx;
            double dispX;

            double c = a - fxA / (fxB - fxA) * (b - a);
            double fxC = PolStr.EvalPolStr(_polinom, c, 0);

            if (fxA * fxC > 0)
            {
                x0 = b;
            }
            else
            {
                x0 = a;
            }

            answ[0] = x0;
            answ[1] = PolStr.EvalPolStr(_polinom, answ[0], 0);

            do
            {
                double fxLastX = answ[1];

                double test1 = PolStr.EvalPolStr(_polinom, answ[0], 1);
                answ[0] = answ[0] - answ[1] / test1;
                answ[1] = PolStr.EvalPolStr(_polinom, answ[0], 0);

                if ((fxA * answ[1]) > 0)
                {
                    a = answ[0];
                    fxA = PolStr.EvalPolStr(_polinom, a, 0);
                }
                else
                {
                    b = answ[0];
                    fxB = PolStr.EvalPolStr(_polinom, b, 0);
                }

                dispFx = Math.Abs(answ[1] - fxLastX);
                dispX = Math.Abs(answ[0] - x0);

                x0 = answ[0];

            }
            while ((dispFx >= _disp) || (dispX >= _disp));

            _b = Math.Min(a, b);

            return answ;
        }*/

        //Собственный вектор
        public MyMatrix EigenVector(double _eigen)
        {
            MyMatrix y = new MyMatrix(row, 1);
            for (uint i = 0; i < row; i++)
                y[i, 0] = Math.Pow(_eigen, row - i - 1);

            return S()[0] * y;
        }

        //Получить полином в строке
        private static string GetPolin(double[] values)
        {
            string f = "";

            //if (values.Count() % 2 != 0)
                //f += "-1*(";

            for (uint i = 0; i < values.Count() + 1; i++)
            {
                if (i != 0)
                {
                    double buf = values[i - 1] * -1;

                    if (!(buf < 0))
                        f += "+";

                    f += buf;

                    if (i != values.Count())
                        f += "*";
                }

                for (uint j = 0; j < values.Count() - i; j++)
                {
                    f += "x";

                    if (j == values.Count() - i - 1)
                        break;

                    f += "*";
                }
            }
            //if (values.Count() % 2 != 0)
                //f += ")";

            return f.Replace(',', '.');
        }

        //Соразмерная единичная матрица
        public MyMatrix GetUnit()
        {
            double[] unit = new double[row * row];
            for(uint i = 0; i < row; i++)
            {
                unit[i * row + i] = 1.0;
            }

            MyMatrix answ = new MyMatrix(row, row, unit);

            return answ;
        }

        //Матрица фробениуса
        public MyMatrix Frob()
        {
            MyMatrix[] s = S();

            MyMatrix p = s[1] * this * s[0];

            return p;
        }

        //Найти S
        private MyMatrix[] S()
        {
            MyMatrix[] a = new MyMatrix[row];
            a[0] = this.Clone();

            MyMatrix[,] m = new MyMatrix[row-1, 2];

            for (uint i = 1; i < row; i++)
            {
                m[i - 1, 0] = M(row - i, false, a[i - 1]);
                m[i - 1, 1] = M(row - i, true, a[i - 1]);

                a[i] = m[i-1,1] * a[i - 1] * m[i - 1, 0];
            }

            MyMatrix[] _S = new MyMatrix[2];

            _S[0] = m[0, 0];
            _S[1] = m[row-2, 1];

            for(uint i = 1; i < row-1; i++)
            {
                _S[0] *= m[i,0];
                _S[1] *= m[row - 2 - i, 1];
            }

            return _S;
        }

        //Найти M
        private MyMatrix M(uint _k, bool _inv, MyMatrix _a)
        {
            MyMatrix _M = new MyMatrix(row, row);

            --_k;

            if(_inv)
            {
                for(uint i = 0; i < row; i++)
                {
                    for(uint j = 0; j < row; j++)
                    {
                        if(i == _k)
                        {
                            _M[i, j] = _a[i + 1, j];
                            continue;
                        }

                        if(i==j)
                        {
                            _M[i, j] = 1;
                            continue;
                        }

                        _M[i, j] = 0;
                    }
                }
            }
            else
            {
                for (uint i = 0; i < row; i++)
                {
                    for (uint j = 0; j < row; j++)
                    {
                        if((i == _k) && (j == _k))
                        {
                            _M[i, j] = 1 / _a[_k+1, _k];

                            continue;
                        }

                        if(i == _k)
                        {
                            _M[i, j] = -(_a[_k + 1, j] / _a[_k + 1, _k]);

                            continue;
                        }

                        if(i == j)
                        {
                            _M[i, j] = 1;

                            continue;
                        }

                        _M[i, j] = 0;
                    }
                }
            }

            return _M;
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

            return answ;
        }

        //Получить строку матрицы до end
        public double[] GetString(uint _num, uint end = 0)
        {
            double[] ai = new double[col];
            for (uint j = 0; j < col-end; j++)
            {
                ai[j] = data[_num * col + j];
            }

            return ai;
        }

        //Получить колонку матрицы до end
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
