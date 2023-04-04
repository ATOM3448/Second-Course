using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace lab6
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                MyMatrix mat1 = new MyMatrix();
                Console.WriteLine(mat1.ToString());

                double[] data = null;
                MyMatrix mat2 = new MyMatrix(3, data);
                Console.WriteLine(mat2.ToString());

                MyMatrix mat3 = new MyMatrix(mat1 * mat2);
                Console.WriteLine(mat3.ToString());

                mat3 = new MyMatrix(mat1 * 6);
                Console.WriteLine(mat3.ToString());

                mat3 = new MyMatrix(mat1 + mat2);
                Console.WriteLine(mat3.ToString());

                mat3 = new MyMatrix(mat1 - mat2);
                Console.WriteLine(mat3.ToString());
            }

            catch(ArgumentException ex)
            {
                Console.WriteLine(ex.ToString());
            }

            Console.ReadKey();
        }
    }
}
