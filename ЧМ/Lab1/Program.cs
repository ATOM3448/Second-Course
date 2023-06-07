using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.IO;
using PolStrLib;

//Знаки в циклах погр. вместо > >=

namespace LabOne
{
    class Program
    {
        static void Main(string[] args)
        {
            //Переменные ввода
            uint mode;
            string expr;
            double taskDisp;
            double a;
            double b;

            //Путь к файлам
            string pathIn = @"D:\Math Metods\LabOne\LabOne\IN.txt";
            string pathOut = @"D:\Math Metods\LabOne\LabOne\OUT.txt";

            if (!File.Exists(pathIn))
            {
                Console.WriteLine("Нет доступа к файлу ввода");
                Console.ReadLine();
                return;
            }
            if (!File.Exists(pathOut))
            {
                Console.WriteLine("Нет доступа к файлу вывода");
                Console.ReadLine();
                return;
            }

            StreamReader sr = new StreamReader(pathIn);

            mode = Convert.ToUInt32(sr.ReadLine().ToString());

            expr = sr.ReadLine().ToString();

            a = Convert.ToInt32(sr.ReadLine().ToString());
            b = Convert.ToInt32(sr.ReadLine().ToString());

            taskDisp = Convert.ToDouble(sr.ReadLine().ToString());

            Function fx = new Function(expr, a, b);
            

            sr.Close();

            switch (mode)
            {
                //Метод дихотомии
                case 0:

                    fx.Dichotomies(taskDisp, 50);

                    break;

                //Метод хорд
                case 1:

                    fx.Chord(taskDisp, 18000);

                    break;

                //Метод золотого сечения
                case 2:

                    fx.GoldenSection(taskDisp, 50);

                    break;

                //Метод Ньютона
                case 3:

                    fx.Newton(taskDisp, 50);

                    break;

                //Метод итераций
                case 4:

                    fx.Iteration(taskDisp, 200000); 

                    break;

                //Метод комбинированый
                case 5:

                    fx.Comb(taskDisp, 50);

                    break;

                default:
                    Console.WriteLine("Ошибка выбора режима работы.");
                    break;
            };
            StreamWriter sw = new StreamWriter(pathOut);

            double answ = fx.GetX();
            answ = answ - answ % taskDisp;

            Console.WriteLine(answ);
            sw.WriteLine(answ);

            double fxValue = fx.GetFxX();
            fxValue = fxValue - fxValue % taskDisp;
            Console.WriteLine(fxValue);
            sw.WriteLine(fxValue);

            Console.WriteLine(fx.GetDispFx() + " / " + fx.GetDispX());
            sw.WriteLine(fx.GetDispFx() + " / " + fx.GetDispX());

            sw.Close();

            Console.ReadLine();
        }
    }
}
