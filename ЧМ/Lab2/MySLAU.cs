using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using System.Xml.XPath;

namespace Lab2
{
    class MySLAU
    {
        public MySLAU(uint _n, double[] _dataMatrix, double[] _dataB)
        {
            mat = new MyMatrix(_n, _n, _dataMatrix);
            x = new MyMatrix(_n, 1);
            b = new MyMatrix(_n, 1, _dataB);

            //Расширенная единичная матрица
            double[] _unitData = new double[(_n+1) * (_n+1)];
            for(int i = 0; i < (_n+1); i++)
            {
                _unitData[i * (_n+1) + i] = 1;
            }
            unitMat = new MyMatrix(_n+1, _n+1, _unitData);
        }

        public void Orthogonalization()
        {
            uint row = mat.Row+1;
            uint col = mat.Col+1;

            double[] dataExtMat = new double[row * col];
            double[] _dataMat = mat.Data;
            double[] _dataB = b.Data;
            double[] _unitData = unitMat.Data;

            for (int i = 0; i < row; i++)
            {
                for (int j = 0; j < col; j++)
                {
                    if (i == (row - 1))
                    {
                        dataExtMat[i * col + j] = _unitData[i * col + j];
                        continue;
                    }

                    if(j == (col-1))
                    {
                        dataExtMat[i * col + j] = -_dataB[i];
                        continue;
                    }

                    dataExtMat[i * col + j] = _dataMat[i * (col-1) + j];
                }
            }
            ortog_extendedMat = new MyMatrix(row, col, dataExtMat);

            double[] dataExtX = new double[col];
            double[] _dataX = x.Data;
            for(int i = 0; i < (col-1); i++)
            {
                dataExtX[i] = _dataX[i];
            }
            dataExtX[col - 1] = 1;
            ortog_extendedX = new MyMatrix(1, col, dataExtX);

            //Находим A
            A();

            //Нахождение X ext
            for(uint i = 0; i < row-1; i++)
            {
                double up = ortog_finalA[row - 1, i];
                double down = ortog_finalA[row - 1, col - 1];
                x[0, i] = up / down;
            }

            StreamWriter sw = new StreamWriter("D:/ЧМ/Lab2/Lab2/OUT.txt");

            sw.WriteLine(ortog_extendedMat);
            sw.WriteLine("\n");
            sw.WriteLine(ortog_finalA);
            sw.WriteLine("\n");
            sw.WriteLine(x);
            sw.WriteLine("\n");

            MyMatrix E = mat * x - b;

            sw.WriteLine(E);
            sw.WriteLine("\n");

            double normE = 0;

            for (uint i = 0; i < E.Row; i++)
            {
                for (uint j = 0; j < E.Col; j++)
                {
                    normE += E[i, j] * E[i, j];
                }
            }

            normE = Math.Sqrt(normE);

            sw.WriteLine(normE);

            sw.Close();
        }

        private void A()
        {
            uint row = ortog_extendedMat.Row;
            uint col = ortog_extendedMat.Col;

            //Массив значений матрицы A
            double[] dataA = new double[row * col];

            for(uint i = 0; i < row; i++)
            {
                //Извлекаем строку i из которой будем вычитать
                double[] ai = ortog_extendedMat.GetString(i);

                //Строка, что будем вычитать
                double[] deductible = new double[col];
                

                for (uint j = 0; j < i; j++)
                {
                    // Получаем aj
                    double[] aj = new double[col];
                    for(int k = 0; k < col; k++)
                    {
                        aj[k] = dataA[j * col + k];
                    }

                    double sp = ScalProd(ai, aj);
                    
                    for(uint k = 0; k < col; k++)
                    {
                        deductible[k] += sp * aj[k];
                    }
                }

                //Получаем строку матрицы A
                double[] ai_deducatible = new double[col];
                for (uint j = 0; j < col; j++)
                {
                    ai_deducatible[j] = ai[j] - deductible[j];
                }

                double norm = Math.Sqrt(ScalProd(ai_deducatible, ai_deducatible));

                for (uint j = 0; j < col; j++)
                {
                    dataA[i * col + j] += ai_deducatible[j] / norm;
                }
            }

            ortog_finalA = new MyMatrix(row, col, dataA);
        }

        private static double ScalProd(double[] _left, double[] _right)
        {
            double sum = 0;
            int len = _left.Count();
            for(int i = 0; i < len; i++)
            {
                sum += _left[i] * _right[i];
            }

            return sum;
        }

        public void Iterations(double _disp = 0.0001)
        {
            double[] loc_bData = new double[mat.Row];
            
            for(uint i = 0; i < mat.Row; i++)
            {
                loc_bData[i] = b[i, 0] / mat[i, i];
            }

            MyMatrix loc_b = new MyMatrix(mat.Row, 1, loc_bData);

            double[] loc_aData = new double[mat.Row * mat.Row];

            for(uint i = 0; i < mat.Col; i++)
            {
                for(uint j = 0; j < mat.Col; j++)
                {
                    if(i == j)
                    {
                        loc_aData[i * mat.Col + i] = 0;
                        continue;
                    }

                    loc_aData[i * mat.Col + j] = -(mat[i, j] / mat[i, i]);
                }
            }

            MyMatrix loc_a = new MyMatrix(mat.Row, mat.Row, loc_aData);

            double accuracy = 0;

            for (uint i = 0; i < mat.Col; i++)
            {
                for (uint j = 0; j < mat.Col; j++)
                {
                    accuracy += loc_a[i, j] * loc_a[i, j];
                }
            }

            accuracy = Math.Sqrt(accuracy);

            accuracy = ((1 - accuracy) / accuracy) * _disp;

            x = loc_b.Clone();
            MyMatrix lastX = x.Clone();

            do
            {
                for(uint i = 0; i < mat.Col; i++)
                {
                    double sum = 0;
                    for (uint j = 0; j < mat.Col;j++)
                    {

                        sum += loc_a[i, j] * lastX[j, 0];
                    }
                    x[i, 0] = sum + loc_b[i, 0];
                }

                lastX = x - lastX;

                if (Math.Sqrt(ScalProd(lastX.Data, lastX.Data)) < accuracy)
                {
                    break;
                }

                for (uint i = 0; i < mat.Row; i++)
                {
                    lastX[i, 0] = x[i, 0];
                }

            } while (true);

            StreamWriter sw = new StreamWriter("D:/ЧМ/Lab2/Lab2/OUT.txt");

            sw.WriteLine(x);
            sw.WriteLine("\n");

            MyMatrix E = mat * x - b;

            sw.WriteLine(E);
            sw.WriteLine("\n");

            double normE = 0;

            for (uint i = 0; i < E.Row; i++)
            {
                for (uint j = 0; j < E.Col; j++)
                {
                    normE += E[i, j] * E[i, j];
                }
            }

            normE = Math.Sqrt(normE);

            sw.WriteLine(normE);

            sw.Close();
        }

        public MyMatrix ortog_finalA;
        private MyMatrix unitMat; 
        private MyMatrix mat;
        public MyMatrix ortog_extendedMat;
        public MyMatrix x;
        private MyMatrix ortog_extendedX;
        private MyMatrix b;

    }
}
