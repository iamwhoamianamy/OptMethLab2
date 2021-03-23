#pragma once
#include <vector>
#include "GoldenRatio.h"
#include "Vector.h"

class DanPshen
{
public:

   const int size;            // Размерность вектора

   vector<double> Sk;         // Минус гардиент на текущем шаге
   vector<double> Sk1;        // Минус градиент от нового приближения

   vector<double> xk;         // Приближение на текущем шаге
   vector<double> xk1;        // Новое приближение

   vector<double> grad_xk1;   // Вспомогательный вектор для нахождения экстремума

   DanPshen() : size(0)
   {

   }

   DanPshen(const int& t_size) : size(t_size)
   {
      Sk.resize(size);
      Sk1.resize(size);

      xk.resize(size);
      xk1.resize(size);

      grad_xk1.resize(size);
   }

   void FindExtremum(double f(const vector<double>&), const vector<double>& x0, const double& eps)
   {
      // 1. Расчет градиента функции f в точке xk
      CalcGrad(f, x0, Sk);

      Sk *= -1;

      xk = x0;

      int k = 0;
      do
      {
         // 2. Минимизация функции f по направлению Sk
         Function to_minimize = Function(xk, Sk);
         double lambda = to_minimize.FindMinArg(f, eps);

         // Получение нового приближения
         xk1 = xk + lambda * Sk;

         // 3. Вычисление grad(f(xk1)) и весового коэффициента omega

         CalcGrad(f, xk1, grad_xk1);
         //grad_xk1 *= -1;

         //double omega = (-1 * Sk * (-1 * Sk - grad_xk1)) / (grad_xk1 *(-1 * Sk));
         double omega = (grad_xk1 * grad_xk1) / (Sk * Sk);

         // 4. Определение новго направления Sk1
         Sk = -1 * grad_xk1 + omega * Sk;

         xk = xk1;

      } while(Norm(Sk) > eps);
   }


   void CalcGrad(double funct(const vector<double>&), const vector<double>& point, vector<double>& res)
   {
      const double eps = 1e-8;

      for(int i = 0; i < size; i++)
      {
         vector<double> t(size);

         t[i] = point[i];

         res[i] = -funct(t);

         t[i] += eps;

         res[i] += funct(t);

         res[i] /= eps;
      }
   }
};
