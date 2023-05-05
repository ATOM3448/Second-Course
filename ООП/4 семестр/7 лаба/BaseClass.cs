using System;
using System.Collections;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Numerics;

namespace Lab_7
{
    abstract class BaseClass : IEnumerable, IFormattable, ICloneable
    {
        // Основные поля
        protected double[] data;
        protected uint row;
        protected uint col;
        protected uint id;

        // Гет\Сет
        public double[] Data { get { return data; } protected set { data = value; } }
        public uint Row { get { return row; } protected set { row = value; } }
        public uint Col { get { return col; } protected set { col = value; } }
        public uint Id { get { return id; } protected set { id = value; } }
        public abstract uint Counter();

        // Конструктор
        protected BaseClass(uint _row, uint _col, double[] _data, uint _counter)
        {
            row = _row;
            col = _col;
            id = _counter;
            data = new double[row * col];

            if(_data != null)
            {
                _data.CopyTo(data, 0);
                return;
            }

            for (uint i = 0; i < (col * row); i++)
            {
                data[i] = i + 1;
            }
        }

        // Минимум
        public double Min()
        {
            return data.Min();
        }

        // Максимум
        public double Max()
        {
            return data.Max();
        }

        // Проверка на возможность сложения
        public bool CheckAdd(BaseClass _other)
        {
            if((row == _other.row) && (col == _other.col))
            {
                return true;
            }
            return false;
        }

        // Проверка на возможность умножения
        public virtual bool CheckMul(BaseClass _other)
        {
            if(col == _other.row)
            {
                return true;
            }
            return false;
        }

        // Индексатор одномерный
        public double this[uint _i]
        {
            get { return data[_i]; }
            set { data[_i] = value; }
        }

        // Индексатор двумерный
        public double this[uint _i, uint _j]
        {
            get { return data[_i * col + _j]; }
            set { data[_i * col + _j] = value; }
        }

        // Конвертация в строку
        public override string ToString()
        {
            return ToString("M");
        }

        // Конвертация в строку c указанием формата
        public string ToString(string _format)
        {
            if(string.IsNullOrEmpty(_format))
            {
                _format = "M";
            }

            string toOut = "";

            switch(_format.ToUpperInvariant())
            {
                case "M":
                    for(uint i = 0; i < row; i++)
                    {
                        for(int j = 0; j < col; j++)
                        {
                            toOut += string.Format("{0,8:0.##}", data[i * col + j]);
                        }
                        toOut += "\n";
                    }

                    return toOut;

                case "L":
                    for (uint i = 0; i < row; i++)
                    {
                        for (int j = 0; j < col; j++)
                        {
                            toOut += string.Format("{0,8:0.##}", data[i * col + j]);
                        }
                    }

                    return toOut;

                default:
                    throw new ArgumentException("Некорректный формат");
            }
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

    }
}
