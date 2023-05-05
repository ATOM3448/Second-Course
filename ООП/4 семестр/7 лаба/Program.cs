using System;

namespace Lab_7
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                // Проверка конструкторов матрицы
                MyMatrix mat1 = new MyMatrix();             // По умолчанию
                MyMatrix mat2 = new MyMatrix(4);            // Квадратная
                double[] data = {5, 6, 7, 2, 7, 9, 23, 6.2 }; 
                MyMatrix mat3 = new MyMatrix(2, 4, data);   // Кастом
                MyMatrix mat4 = new MyMatrix(mat3);         // Копирование

                // Проверка конструкторов вектора
                MyVector vect1 = new MyVector();            // По умолчанию
                MyVector vect2 = new MyVector(8, data);     // Кастом
                MyVector vect3 = new MyVector(vect2);       // Копирование

                // Вывод матриц
                Console.WriteLine("Матрица. По умолчанию:\n" + mat1 + "\n");
                Console.WriteLine("Матрица. Квадратная:\n" + mat2 + "\n");
                Console.WriteLine("Матрица. Кастом:\n" + mat3 + "\n");
                Console.WriteLine("Матрица. Копирование:\n" + mat4 + "\n");

                // Разделение блоков
                Console.WriteLine("-------------------------------\n\n");

                // Вывод векторов
                Console.WriteLine("Вектор. По умолчанию:\n" + vect1 + "\n");
                Console.WriteLine("Вектор. Кастом:\n" + vect2 + "\n");
                Console.WriteLine("Вектор. Копирование:\n" + vect3 + "\n");

                // Разделение блоков
                Console.WriteLine("-------------------------------\n\n");

                // Проверка метода вращения
                Console.WriteLine("Вектор. Вращение:\n" + vect3.Rotate());

                // Разделение блоков
                Console.WriteLine("-------------------------------\n\n");

                //Проверка перемножения матриц и векторов
                Console.WriteLine("Матрица. Перемножение:\n" + (mat3 *= mat2) + "\n");
                Console.WriteLine("Вектор. Перемножение:\n" + (vect2 *= vect3.Rotate()) + "\n");

                // Разделение блоков
                Console.WriteLine("-------------------------------\n\n");

                // Проверка перемножения матриц и векторов на скаляры
                Console.WriteLine("Матрица. Перемножение на скаляр:\n" + (mat2 *= 5) + "\n");
                Console.WriteLine("Вектор. Перемножение на скаляр:\n" + (vect3 *= 2) + "\n");

                Console.WriteLine("-------------------------------\n\n");

                // Проверка сложения и вычитания матрицы и вектора
                Console.WriteLine("Матрица. Сумма:\n" + (mat2 += mat2) + "\n");
                Console.WriteLine("Вектор. Сумма:\n" + (vect3 += vect2) + "\n");
                Console.WriteLine("Матрица. Разность:\n" + (mat2 -= mat2) + "\n");
                Console.WriteLine("Вектор. Разность:\n" + (vect3 -= vect2) + "\n");

                // Проверка перемножения матрицы на вектор
                Console.WriteLine("Матрица на вектор:\n" + (mat1 *= vect1.Rotate()) + "\n");
            }
            catch (ArgumentException ex)
            {
                Console.WriteLine(ex.ToString());
            }

            Console.ReadKey();
        }
    }
}