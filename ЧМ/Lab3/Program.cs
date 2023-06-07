using System;
using System.Data;
using System.IO;
using Lab2;

namespace Lab3
{
    class Program
    {
        static void Main(string[] args)
        {
            UInt16 mode;
            uint n;
            double[] matData;

            string pathIn = "D:\\ЧМ\\Lab3\\Lab3\\IN.txt";
            string pathOut = "D:\\ЧМ\\Lab3\\Lab3\\OUT.txt";

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

            // Данные ввода
            mode = Convert.ToUInt16(sr.ReadLine());
            n = Convert.ToUInt32(sr.ReadLine());
            matData = new double[n * n];

            for (uint i = 0; i < n; i++)
            {
                int ind = 0;
                string nums = sr.ReadLine();
                foreach (var num in nums.Split())
                    matData[i * n + (ind++)] = Convert.ToDouble(num);
            }

            sr.Close();

            MyMatrix taskMat = new MyMatrix(n, n, matData);

            StreamWriter sw = new StreamWriter(pathOut);

            double[,] eigen = taskMat.EigenValues(in sw);

            for (uint i = 0; i < n; i += (uint)eigen[i, 1])
            {
                sw.WriteLine("Собственное число {0}: {1}", i, eigen[i, 0]);
                sw.WriteLine("Проверка собственного числа {0}: {1}", i, taskMat.CheckEigen(eigen[i, 0]));
                
                if (mode == 2)
                {

                    MyMatrix vect = taskMat.EigenVector(eigen[i, 0]);

                    sw.WriteLine("\n\nСобственный вектор {0}:\n{1}", i, vect);

                    sw.WriteLine("Проверка собственного вектора {0}:\n{1}", i, taskMat.CheckEigenVect(vect, eigen[i, 0]));
                }

                sw.WriteLine("\nКратность собственного числа {0}: {1}\n", i, eigen[i, 1]);
            }

            sw.Close();
        }
    }
}
