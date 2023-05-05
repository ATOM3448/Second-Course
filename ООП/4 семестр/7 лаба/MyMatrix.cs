using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7
{
    class MyMatrix : BaseClass
    {
        private static uint counter = 0;

        // Конструктор кастом
        public MyMatrix(uint _row, uint _col, double[] _data = null) : base(_row, _col, _data, counter++)
        {
            Console.WriteLine("Конструктор для кастомной матрицы #{0}", id);
        }

        // Конструктор по умолчанию
        public MyMatrix() : this(3, 3)
        {
            Console.WriteLine("Стандартный конструктор для матрицы #{0}", id);
        }

        // Конструктор квадратной матрицы
        public MyMatrix(uint _size, double[] _data = null) : this(_size, _size, _data)
        {
            Console.WriteLine("Конструктор для квадратной матрицы #{0}", id);
        }

        // Конструктор копирования
        public MyMatrix(MyMatrix _obj) : this(_obj.row, _obj.col, _obj.data)
        {
            Console.WriteLine("Конструктор копирования для матрицы #{0}", id);
        }

        public override uint Counter()
        {
            return counter;
        }

        // Умножение
        public static MyMatrix operator*(MyMatrix _operand1, BaseClass _operand2)
        {
            if (!_operand1.CheckMul(_operand2))
            {
                throw new ArgumentException("Данные объкты нельзя перемножать");
            }
            
            uint _col = _operand2.Col;

            MyMatrix toOut = new MyMatrix(_operand1.row, _col);

            for (uint i = 0; i < _operand1.row; i++)
            {
                for (uint j = 0; j < _col; j++)
                {
                    toOut[i, j] = 0;
                    for (uint k = 0; k < _operand1.col; k++)
                    {
                        toOut[i, j] += (_operand1[i, k] * _operand2[k, j]);
                    }
                }
            }

            return toOut;
        }

        // Умножение на скаляр
        public static MyMatrix operator*(MyMatrix _operand1, double _operand2)
        {
            MyMatrix toOut = new MyMatrix(_operand1);

            for(uint i = 0; i < _operand1.row; i++) 
            {
                for (uint j = 0; j < _operand1.col; j++)
                {
                    toOut[i, j] *= _operand2;
                }
            }

            return toOut;
        }

        // Сложение
        public static MyMatrix operator+(MyMatrix _operand1, BaseClass _operand2)
        {
            if(!_operand1.CheckAdd(_operand2))
            {
                throw new ArgumentException("Данные объкты нельзя складывать");
            }

            MyMatrix toOut = new MyMatrix(_operand1);

            for(uint i = 0; i < _operand1.row; i++)
            {
                for (uint j = 0; j < _operand1.col; j++)
                {
                    toOut[i, j] += _operand2[i, j];
                }
            }

            return toOut;
        }


        // Вычитание
        public static MyMatrix operator-(MyMatrix _operand1, BaseClass _operand2)
        {
            if (!_operand1.CheckAdd(_operand2))
            {
                throw new ArgumentException("Данные объкты нельзя складывать");
            }

            MyMatrix toOut = new MyMatrix(_operand1);

            for (uint i = 0; i < _operand1.row; i++)
            {
                for (uint j = 0; j < _operand1.col; j++)
                {
                    toOut[i, j] -= _operand2[i, j];
                }
            }

            return toOut;
        }
    }
}
