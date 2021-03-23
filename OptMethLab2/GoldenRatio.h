#pragma once
#include <cmath>
#include <vector>
#include "Vector.h"

using namespace std;

const double SQRT5 = sqrt(5);

class Function
{
public:
   vector<double> xk;
   vector<double> Sk;

   Function()
   {

   }

   Function(const vector<double>& t_xk, const vector<double>& t_Sk) : xk(t_xk), Sk(t_Sk)
   {

   };

   double GetValue(double funct(const vector<double>&), const double& lambda)
   {
      return funct(xk + lambda * Sk);
   }

   // Поиск аргумента минимума функции методом золотого сечения
   double FindMinArg(double funct(const vector<double>&), const double& eps)
   {
      double a = -50, b = 100;
      double x1 = a + (3 - SQRT5) / 2 * (b - a);
      double x2 = a + (SQRT5 - 1) / 2 * (b - a);
      double f1, f2, a1, b1;

      int n = 0;
      for(; abs(b - a) > eps; n++)
      {
         f1 = GetValue(funct, x1), f2 = GetValue(funct, x2);
         a1 = a, b1 = b;

         if(f1 < f2)
         {
            b = x2;
            x2 = x1;
            x1 = a + (3 - SQRT5) / 2 * (b - a);
         }
         else
         {
            a = x1;
            x1 = x2;
            x2 = a + (SQRT5 - 1) / 2 * (b - a);
         }
      }

      return a;
   }
};