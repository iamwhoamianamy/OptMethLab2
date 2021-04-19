#pragma once
#include <vector>
#include "Lab2Data.h"
#include "Vector.h"

class Newton
{
public:
   int size = 2;               // Размерность вектора
   vector<vector<double>> H;   // Матрица Гёссе
   vector<vector<double>> IH;  // Обратная матрица Гёссе

   vector<double> t;           // Вспомогательный вектор для расчета Гессиана

   vector<double> grad;        // Гардиент на текущем шаге

   vector<double> xk;          // Приближение на текущем шаге
   vector<double> xk1;         // Новое приближение

   vector<double> Sk;          // Напрвление поиска

   int f_calc_count = 0;       // Число вычислений функции

   Newton() : size(2)
   {
      H.resize(2, vector<double>(2));
      IH.resize(2, vector<double>(2));
      t.resize(2);

      grad.resize(2);

      xk.resize(2);
      xk1.resize(2);

      Sk.resize(2);
      t.resize(2);
   }

   // Расчитать Гессиан для двумерной функции (при eps = 1 все нормально)
   void CalcHessian(double funct(const vector<double>&), const vector<double>& point, const double& eps)
   {
      H[0][0] = (funct({ point[0] + 2 * eps, point[1] }) - 2 * funct({ point[0], point[1] }) + funct({ point[0] - 2 * eps, point[1] })) / (4 * eps * eps);
      H[1][0] = (funct({ point[0] + eps, point[1] + eps }) -
                 funct({ point[0] + eps, point[1] - eps }) -
                 funct({ point[0] - eps, point[1] + eps }) +
                 funct({ point[0] - eps, point[1] - eps })) / (4 * eps * eps);
      H[0][1] = H[1][0];
      H[1][1] = (funct({ point[0], point[1] + 2 * eps }) - 2 * funct({ point[0], point[1] }) + funct({ point[0], point[1] - 2 * eps })) / (4 * eps * eps);
   }

   // Расчитать обратную матрицу Гессе
   void CalcInverseHessian()
   {
      double a = H[0][0];
      double b = H[0][1];
      double c = H[1][0];
      double d = H[1][1];

      double q = 1.0 / (a * d - b * c);

      IH[0][0] = q * d;
      IH[0][1] = q * -b;
      IH[1][0] = q * -c;
      IH[1][1] = q * a;
   }

   void CalcGrad(double funct(const vector<double>&), const vector<double>& point, vector<double>& res, const double& grad_eps)
   {
      res[0] = (funct({ point[0] + grad_eps, point[1] }) - funct({point[0] - grad_eps, point[1] })) / (2 * grad_eps);
      res[1] = (funct({ point[0], point[1] + grad_eps }) - funct({point[0], point[1] - grad_eps })) / (2 * grad_eps);
   }

   // Матрично-векторное умножение
   void MatVecMult(const vector<vector<double>>& matrix, const vector<double>& vec, vector<double>& res)
   {
      res.resize(2);

      res[0] = matrix[0][0] * vec[0] + matrix[0][1] * vec[1];
      res[1] = matrix[1][0] * vec[0] + matrix[1][1] * vec[1];
   }
   

   int FindExtremum(double funct(const vector<double>&),
                    int min_max(double f(const vector<double>&), const vector<double>&, const vector<double>&, const double&, double&),
                    const vector<double>& x0,
                    const double& f_eps, const double& xs_eps, const double& grad_eps,
                    ofstream& fout)
   {

      f_calc_count = 0;
      fout << setw(3) << "k";
      fout << setw(14) << "x" << setw(14) << "y" << setw(14) << "f(x, y)";
      fout << setw(14) << "Sx" << setw(14) << "Sy" << setw(14) << "lambda";
      fout << setw(14) << "|xk - x(k-1)|" << setw(14) << "|yk - y(k-1)|" << setw(14) << "|fk - f(k-1)|";
      fout << setw(14) << "angle";
      fout << setw(14) << "H00" << setw(14) << "H01" << setw(14) << "H10" << setw(14) << "H11" << endl;

      xk = x0;

      bool exit_flag;
      int iter_count = 0;
      do
      {
         CalcHessian(funct, xk, 1e-3);
         f_calc_count += 11;
         CalcInverseHessian();

         if(!(IH[0][0] > 0 && IH[0][0] * IH[1][1] - IH[1][0] * IH[0][1] > 0))
         {
            IH[0][0] = 1;
            IH[0][1] = 0;
            IH[1][0] = 0;
            IH[1][1] = 1;
         }

         
         CalcGrad(funct, xk, grad, grad_eps);
         f_calc_count += 4;
         grad *= -1;

         MatVecMult(IH, grad, Sk);

         // Минимизация функции f по направлению Sk
         double lambda;
         f_calc_count += min_max(funct, xk, Sk, 1e-15, lambda) + 1;
         
         // Получение нового приближения
         xk1 = xk + lambda * Sk;

         // Блок вывода
         fout << fixed << setw(3) << iter_count + 1;
         fout << scientific;
         fout << setw(14) << xk1[0] << setw(14) << xk1[1] << setw(14) << funct(xk1);
         fout << setw(14) << Sk[0] << setw(14) << Sk[1] << setw(14) << lambda;
         fout << setw(14) << abs(xk1[0] - xk[0]) << setw(14) << abs(xk1[1] - xk[1]) << setw(14) << funct(xk1) - funct(xk);
         fout << setw(14) << acos((xk1[0] * Sk[0] + xk1[1] * Sk[1]) / (Norm(xk1) * Norm(grad))) * 180 / PI;
         fout << setw(14) << H[0][0] << setw(14) << H[0][1] << setw(14) << H[1][0] << setw(14) << H[1][1] << endl;

         // Расчет изменения решения на текущей итерации
         exit_flag = true;

         for(int i = 0; i < size; i++)
            if(abs(xk[i] - xk1[i]) > xs_eps)
               exit_flag = false;

         xk = xk1;
         iter_count++;

      } while(iter_count < 1000 && exit_flag == false);

      fout << endl;
      return iter_count;
   }
};