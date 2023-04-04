using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    class MyMatrix : IEnumerable, IFormattable, ICloneable
    {
        private double[] data;
        private uint row { get; set; }
        private uint col { get; set; }
        private static uint newID = 0;
        private uint id { get; set; }

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
                    data[i] = i;
                }
            }

            Console.WriteLine("Работал конструктор №1 для матрицы #{0}", id);
        }

        //2 Конструктор квадратной кастом
        public MyMatrix(uint _size, double[] _data) : this(_size, _size, _data)
        {
            Console.WriteLine("Работал конструктор №2 для матрицы #{0}", id);
        }

        //3 Конструктор копирования
        public MyMatrix(MyMatrix _early) : this(_early.row, _early.col, _early.data)
        {
            Console.WriteLine("Работал конструктор №3 для матрицы #{0}", id);
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

            if ((col == _operand.row) && (row == _operand.col))
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
