using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab_7
{
    class MyVector : BaseClass
    {
        private static uint counter = 0;

        // Конструктор по умолчанию \ кастом
        public MyVector(uint _col = 3, double[] _data = null) : base(1, _col, _data, counter++)
        {
            Console.WriteLine("Стандартный конструктор для вектора #{0}", id);
        }

        // Конструктор копирования
        public MyVector(MyVector _obj) : base(_obj.row, _obj.col, _obj.data, counter++)
        {
            Console.WriteLine("Конструктор копирования для вектора #{0}", id);
        }

        public override uint Counter()
        {
            return counter;
        }

        // Перегрузка метода проверки на возможность перемножения
        public override bool CheckMul(BaseClass _other)
        {
            if ((row == _other.Row) && (col == _other.Col))
            {
                return true;
            }
            return false;
        }

        // Умножение
        public static MyVector operator *(MyVector _operand1, MyVector _operand2)
        {
            if (!_operand1.CheckMul(_operand2))
            {
                throw new ArgumentException("Данные объкты нельзя перемножать");
            }

            MyVector toOut = new MyVector(_operand1);

            for (uint i = 0; i < (toOut.col * toOut.row); i++)
            {
                toOut[i] *= _operand2[i];
            }

            return toOut;
        }

        // Умножение на скаляр
        public static MyVector operator *(MyVector _operand1, double _operand2)
        {
            MyVector toOut = new MyVector(_operand1);

            for (uint i = 0; i < (_operand1.col * _operand1.row); i++)
            {
                toOut[i] *= _operand2;
            }

            return toOut;
        }

        // Сложение
        public static MyVector operator +(MyVector _operand1, BaseClass _operand2)
        {
            if (!_operand1.CheckAdd(_operand2))
            {
                throw new ArgumentException("Данные объкты нельзя складывать");
            }

            MyVector toOut = new MyVector(_operand1);

            for (uint i = 0; i < (_operand1.col * _operand1.row); i++)
            {
                toOut[i] += _operand2[i];
            }

            return toOut;
        }


        // Вычитание
        public static MyVector operator -(MyVector _operand1, BaseClass _operand2)
        {
            if (!_operand1.CheckAdd(_operand2))
            {
                throw new ArgumentException("Данные объкты нельзя складывать");
            }

            MyVector toOut = new MyVector(_operand1);

            for (uint i = 0; i < (_operand1.col * _operand1.row); i++)
            {
                toOut[i] -= _operand2[i];
            }

            return toOut;
        }

        // Вращение
        public MyVector Rotate()
        {
            uint buf = row;
            row = col;
            col = buf;

            return this;
        }
    }
}
