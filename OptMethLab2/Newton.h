#pragma once
#include <vector>
#include "Lab2Data.h"
#include "Function.h"
#include "Vector.h"

class Newton
{
public:
   int size = 2;               // Размерность вектора
   vector<vector<double>> H;   // Матрица Гёссе
   vector<vector<double>> IH;  // Обратная матрица Гёссе

   vector<double> t;           // Вспомогательный вектор для расчета Гессиана

   vector<double> Sk;          // Гардиент на текущем шаге
   vector<double> gradk_1;     // Градиент от нового приближения

   vector<double> xk;          // Приближение на текущем шаге
   vector<double> xk1;         // Новое приближение

   vector<double> IHgrad;      // Вспомогательный вектор для нахождения экстремума

   Newton() : size(2)
   {
      H.resize(2, vector<double>(2));
      IH.resize(2, vector<double>(2));
      t.resize(2);

      Sk.resize(2);
      gradk_1.resize(2);

      xk.resize(2);
      xk1.resize(2);

      IHgrad.resize(2);
      t.resize(2);
   }

   // Расчитать Гессиан для двумерной функции (при eps = 1 все нормально)
   void CalcHessian(double funct(const vector<double>&), const vector<double>& point, const double& eps)
   {
      H[0][0] = (funct({ point[0] - 2 * eps, point[1] }) - 2 * funct({ point[0], point[1] }) + funct({ point[0] + 2 * eps, point[1] })) / (4 * eps * eps);
      H[1][0] = (funct({ point[0] - eps, point[1] - eps }) -
                 funct({ point[0] - eps, point[1] + eps }) -
                 funct({ point[0] + eps, point[1] - eps }) +
                 funct({ point[0] + eps, point[1] + eps })) / (4 * eps * eps);
      H[0][1] = H[1][0];
      H[1][1] = (funct({ point[0], point[1] - 2 * eps }) - 2 * funct({ point[0], point[1] }) + funct({ point[0], point[1] + 2 * eps })) / (4 * eps * eps);
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
   

   int FindMinimum(double f(const vector<double>&), const vector<double>& x0, const double& eps, const double& grad_eps)
   {
      CalcHessian(f, x0, 1e-1);

      if(H[0][0] > 0 && H[0][0] * H[1][1] - H[1][0] * H[0][1] > 0)
      {
         CalcInverseHessian();
         CalcGrad(f, x0, Sk, grad_eps);
         MatVecMult(IH, Sk, IHgrad);
         xk1 = x0 - IHgrad;

         return 1;
      }
      else
      {
         cout << "Hessian is not positive-defined!" << endl;

         return 0;
      }
      
      //xk = x0;

      //bool exit_flag;
      //int iter_count = 0;
      //do
      //{
      //   CalcHessian(f, xk, 1e-1);

      //   if(H[0][0] > 0 && H[0][0] * H[1][1] - H[1][0] * H[0][1] > 0)
      //      CalcInverseHessian();
      //   else
      //   {
      //      H[0][0] = abs(H[0][0]);
      //      H[0][1] = abs(H[0][1]);
      //      H[1][0] = abs(H[1][0]);
      //      H[1][1] = abs(H[1][1]);

      //      CalcInverseHessian();
      //   }

      //   
      //   CalcGrad(f, x0, Sk, grad_eps);
      //   Sk *= -1;

      //   MatVecMult(IH, Sk, IHgrad);

      //   // Минимизация функции f по направлению Sk
      //   Function to_minimize = Function(xk, IHgrad);
      //   double lambda = to_minimize.FindMinArgGolden(f, 1e-15);
      //   
      //   // Получение нового приближения
      //   xk1 = xk + lambda * IHgrad;

      //   // Расчет изменения решения на текущей итерации
      //   exit_flag = true;

      //   for(int i = 0; i < size; i++)
      //      if(abs(xk[i] - xk1[i]) > 1e-16)
      //         exit_flag = false;

      //   xk = xk1;
      //   iter_count++;

      //} while(iter_count < 100 && exit_flag == false);

      //return iter_count;
   }
};