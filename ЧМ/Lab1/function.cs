using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using PolStrLib;


namespace LabOne
{
    class Function
    {
        public Function(string _fxIn, double _a, double _b)
        {
            fx = _fxIn;
            PolStr.StrToPolStr(fx, out fxPol, 0);
            if(PolStr.Error != Error.OK)
            {
                Console.WriteLine("Произошла ошибка при конвертации выражения. Дальнейшие вычисления могут быть ошибочными");
            }

            a = _a;
            b = _b;
        }

        public string GetPol()
        {
            return fxPol;
        }

        public string GetFx()
        {
            return fx;
        }

        public double GetX()
        {
            return x;
        }

        public double GetFxX()
        {
            return fxX;
        }

        public double GetDispFx()
        {
            return dispFx;
        }

        public double GetDispX() 
        {
            return dispX;
        }

        public double Dichotomies(double _disp, uint _iteration)
        {
            fxA = PolStr.EvalPolStr(fxPol, a, 0);
            fxB = PolStr.EvalPolStr(fxPol, b, 0);

            do
            {
                x = (a + b) / 2;
                fxX = PolStr.EvalPolStr(fxPol, x, 0);
                if ((fxA * fxX) > 0)
                {
                    a = x;
                    fxA = fxX;
                }
                else
                {
                    b = x;
                    fxB = fxX;
                }

                dispFx = Math.Abs((fxB - fxA) / 2);
                dispX = Math.Abs((b - a) / 2);

                iterationFinal++;

                if (_iteration <= iterationFinal)
                {
                    break;
                }
            }
            while ((dispFx >= _disp) || (dispX >= _disp));

            return x;
        }

        public double Chord(double _disp, uint _iteration)
        {
            fxA = PolStr.EvalPolStr(fxPol, a, 0);
            fxB = PolStr.EvalPolStr(fxPol, b, 0);

            double x0 = a;
            fxX = fxA;

            do
            {
                double fxLastX = fxX;

                x = a - fxA / (fxB - fxA) * (b - a);
                fxX = PolStr.EvalPolStr(fxPol, x, 0);

                if ((fxA * fxX) > 0)
                {
                    a = x;
                    fxA = fxX;
                }
                else
                {
                    b = x;
                    fxB = fxX;
                }

                dispFx = Math.Abs(fxX - fxLastX);
                dispX = Math.Abs(x - x0);

                iterationFinal++;

                if (_iteration <= iterationFinal)
                {
                    break;
                }

                x0 = x;

            }
            while ((dispFx >= _disp) || (dispX >= _disp));

            return x;
        }

        public double GoldenSection(double _disp, uint _iteration)
        {
            fxA = PolStr.EvalPolStr(fxPol, a, 0);
            fxB = PolStr.EvalPolStr(fxPol, b, 0);

            double Y = (Math.Sqrt(5) + 1) / 2;

            do
            {
                double d = a + (b - a) / Y;
                double fxD = PolStr.EvalPolStr(fxPol, d, 0);
                double c = a + (b - a) / Math.Pow(Y, 2);
                double fxC = PolStr.EvalPolStr(fxPol, c, 0);

                if ((fxA * fxD) > 0)
                {
                    a = c;
                    fxA = fxC;
                }
                else
                {
                    b = d;
                    fxB = fxD;
                }

                x = (a + b) / 2;
                fxX = PolStr.EvalPolStr(fxPol, x, 0);

                dispFx = Math.Abs((fxB - fxA) / 2);
                dispX = Math.Abs((b - a) / 2);

                iterationFinal++;

                if (_iteration <= iterationFinal)
                {
                    break;
                }
            }
            while ((dispFx >= _disp) || (dispX >= _disp));

            return x;
        }

        public double Newton(double _disp, uint _iteration)
        {
            fxA = PolStr.EvalPolStr(fxPol, a, 0);
            fxB = PolStr.EvalPolStr(fxPol, b, 0);

            double x0;

            double c = a - fxA / (fxB - fxA) * (b - a);
            double fxC = PolStr.EvalPolStr(fxPol, c, 0);
            if (fxA * fxC > 0)
            {
                x0 = b;
            }
            else
            {
                x0 = a;
            }

            x = x0;
            fxX = PolStr.EvalPolStr(fxPol, x, 0);

            do
            {
                double fxLastX = fxX;

                double test1 = PolStr.EvalPolStr(fxPol, x, 1);
                 x = x - fxX/test1;
                fxX = PolStr.EvalPolStr(fxPol, x, 0);

                if ((fxA * fxX) > 0)
                {
                    a = x;
                    fxA = PolStr.EvalPolStr(fxPol, a, 0);
                }
                else
                {
                    b = x;
                    fxB = PolStr.EvalPolStr(fxPol, b, 0);
                }

                dispFx = Math.Abs(fxX - fxLastX);
                dispX = Math.Abs(x - x0);

                iterationFinal++;

                if (_iteration <= iterationFinal)
                {
                    break;
                }

                x0 = x;

            }
            while ((dispFx >= _disp) || (dispX >= _disp));

            return x;
        }

        public double Iteration(double _disp, uint _iteration)
        {
            fxA = PolStr.EvalPolStr(fxPol, a, 0);
            fxB = PolStr.EvalPolStr(fxPol, b, 0);

            double x0 = a + b/2;
            fxX = PolStr.EvalPolStr(fxPol, x0, 0);

            do
            {
                double fxLastX = fxX;

                x = x - fxX/Math.Max(PolStr.EvalPolStr(fxPol, a, 1), PolStr.EvalPolStr(fxPol, b, 1));
                fxX = PolStr.EvalPolStr(fxPol, x, 0);

                if ((fxA * fxX) > 0)
                {
                    a = x;
                    fxA = PolStr.EvalPolStr(fxPol, a, 0);
                }
                else
                {
                    b = x;
                    fxB = PolStr.EvalPolStr(fxPol, b, 0);
                }

                dispFx = Math.Abs(fxX - fxLastX);
                dispX = Math.Abs(x - x0);

                iterationFinal++;

                if (_iteration <= iterationFinal)
                {
                    break;
                }

                x0 = x;

            }
            while ((dispFx >= _disp) || (dispX >= _disp));

            return x;
        }

        public double Comb(double _disp, uint _iteration)
        {
            fxA = PolStr.EvalPolStr(fxPol, a, 0);
            fxB = PolStr.EvalPolStr(fxPol, b, 0);

            double x0 = a + b / 2;
            fxX = PolStr.EvalPolStr(fxPol, x0, 0);

            do
            {
                double fxLastX = fxX;

                x = (a+b)/2;
                fxX = PolStr.EvalPolStr(fxPol, x, 0);

                double c = a - fxA / (fxB - fxA) * (b - a);
                double fxC = PolStr.EvalPolStr(fxPol, x, 0);

                if ((fxA * PolStr.EvalPolStr(fxPol, a, 2)) > 0)
                {
                    a = a - fxA / PolStr.EvalPolStr(fxPol, a, 1);
                    fxA = PolStr.EvalPolStr(fxPol, a, 0);
                    b = c;
                    fxB = PolStr.EvalPolStr(fxPol, b, 0);
                }
                else
                {
                    b = b - fxB / PolStr.EvalPolStr(fxPol, b, 1);
                    fxB = PolStr.EvalPolStr(fxPol, b, 0);
                    a = c;
                    fxA = PolStr.EvalPolStr(fxPol, a, 0);
                }

                dispFx = Math.Abs((fxB-fxA)/2);
                dispX = Math.Abs((b-a)/2);

                iterationFinal++;

                if (_iteration <= iterationFinal)
                {
                    break;
                }

                x0 = x;

            }
            while ((dispFx >= _disp) || (dispX >= _disp));

            return x;
        }

        private string fx;
        private string fxPol;
        private int iterationFinal;
        private double fxA;
        private double fxB;
        private double fxX;
        private double a;
        private double b;
        private double x;
        private double dispFx;
        private double dispX;
    }
}
