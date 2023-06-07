using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Lab2
{
    class Program
    {
        static void Main(string[] args)
        {
            UInt16 mode;
            uint n;
            double[] cof;
            double[] b;
            double[] x;

            string pathIn = "D:/ЧМ/Lab2/Lab2/IN.txt";
            string pathOut = "D:/ЧМ/Lab2/Lab2/OUT.txt";

            if(!File.Exists(pathIn))
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

            // Данные ввода
            mode = Convert.ToUInt16(sr.ReadLine());
            n = Convert.ToUInt32(sr.ReadLine());
            cof = new double[n * n];
            b = new double[n];
            
            // Считывание СЛАУ
            for(uint i = 0; i < n; i++)
            {

                // Читаем строку
                string line = sr.ReadLine();

                //Счётчик прохода по строке
                int k = -1;

                for(uint j = 0; j < n+1; j++)
                {
                    // Флаг отрицательного числа
                    bool negative = false;

                    // Берём целую часть числа
                    int num = 0;
                    for (++k; line[k] != '.'; k++)
                    {
                        if(line[k] == '-')
                        {
                            negative = true;
                            continue;
                        }
                        num *= 10;
                        num += line[k] - 48;
                    }

                    // Записываем целую часть числа
                    string buf = "";
                    if(negative)
                    {
                        num = -num;
                    }
                    buf += num;

                    // Берём дробную часть
                    num = 0;
                    for (++k; (k != line.Count()) && (line[k] != ' '); k++)
                    {
                        num *= 10;
                        num += line[k] - 48;
                    }

                    // Записываем дробную часть числа
                    buf += ",";
                    buf += num;

                    // Конвертируем и сохраняем
                    if(j == n)
                    {
                        b[i] = Convert.ToDouble(buf);
                        continue;
                    }

                    cof[i * n + j] = Convert.ToDouble(buf);
                }
            }

            MySLAU task;
            MyMatrix task2;
            MyMatrix task2_answ;

            switch (mode)
            {
                case 1:
                    task = new MySLAU(n, cof, b);
                    task.Orthogonalization();
                    break;
                case 2:
                    task = new MySLAU(n, cof, b);
                    task.Iterations(0.0000000001);
                    break;
                case 3:
                    task2 = new MyMatrix(n, n, cof);
                    task2_answ = MyMatrix.Ortog_Inverse(task2);

                    break;
                case 4:
                    task2 = new MyMatrix(n, n, cof);
                    task2_answ = MyMatrix.Iter_Inverse(task2);

                    break;
            }

            Console.ReadKey();
        }
    }
}
