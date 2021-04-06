#pragma once
#include <vector>
#include "Vector.h"
using namespace std;

const double SQRT5 = sqrt(5);
const double PI = 3.14159265;

double f1(const vector<double>& x)
{
   return 100 * pow(x[1] - x[0], 2) + pow(1 - x[0], 2);
}

void gradf1(const vector<double>& x, vector<double>& res)
{
   res = { 202 * x[0] - 2 - 200 * x[1], -200 * x[0] + 200 * x[1] };
}

double f2(const vector<double>& x)
{
   return 100 * pow(x[1] - pow(x[0], 2), 2) + pow(1 - x[0], 2);
}

double f3(const vector<double>& x)
{
   double A1 = 1, A2 = 3, a1 = 2, a2 = 1;
   double b1 = 3, b2 = 1;
   double c1 = 2, c2 = 1;
   double d1 = 3, d2 = 2;

   double brack_1 = (x[0] - a1) / b1;
   double brack_2 = (x[1] - c1) / d1;

   double brack_3 = (x[0] - a2) / b2;
   double brack_4 = (x[1] - c2) / d2;

   double half_1 = A1 / (1 + brack_1 * brack_1 + brack_2 * brack_2);
   double half_2 = A2 / (1 + brack_3 * brack_3 + brack_4 * brack_4);

   return half_1 + half_2;
}

double f4(const vector<double>& x)
{
   return (x[0] - 2) * (x[0] - 2) + (x[1] - 4) * (x[1] - 4) + 1;
}

double f(const vector<double>& x)
{
   return 2 * x[0] + pow(x[1], 3);
}

// Поиск отрезка с минимумом функции
int FindSegmentWithMin(const double& delta, double funct(const vector<double>&),
                        const vector<double>& x, const vector<double>& Sk, double& a, double& b)
{
   double x0 = 0;
   double xk, xk1, xk_1, h = 2;
   double f = funct(x + (x0) * Sk);
   int f_calc_count = 1;

   if(f == funct(x + (x0 + delta) * Sk))
   {
      a = x0;
      b = x0 + delta;
      return 2;
   }
   else if(f == funct(x + (x0 - delta) * Sk))
   {
      a = x0 - delta;
      b = x0;
      return 3;
   }
   else
   {
      if(f > funct(x + (x0 + delta) * Sk))
      {
         xk = x0 + delta;
         h = delta;
         f_calc_count++;
      }
      else if(f > funct(x + (x0 - delta) * Sk))
      {
         xk = x0 - delta;
         h = -delta;
         f_calc_count += 2;
      }
      else
      {
         a = x0 - delta;
         b = x0 + delta;
         return f_calc_count + 2;
      }

      xk_1 = x0;

      bool exit = false;
      do
      {
         h *= 2;
         xk1 = xk + h;

         if(funct(x + (xk)*Sk) > funct(x + (xk1)*Sk))
         {
            xk_1 = xk;
            xk = xk1;
         }
         else
            exit = true;

         f_calc_count += 2;
      } while(!exit);

      a = xk_1;
      b = xk;
   }
   return f_calc_count;
}

// Поиск аргумента минимума функции вдоль направления методом золотого сечения
int FindMinArgGolden(double funct(const vector<double>&),
                        const vector<double>& x, const vector<double>& Sk, const double& eps, double& result)
{
   double a = 0, b = 0;
   int f_calc_count = FindSegmentWithMin(0.1, funct, x, Sk, a, b);

   double x1 = a + (3 - SQRT5) / 2 * (b - a);
   double x2 = a + (SQRT5 - 1) / 2 * (b - a);
   double f1 = funct(x + (x1)*Sk);
   double f2 = funct(x + (x2)*Sk);
   double a1, b1;

   int iter_count = 0;
   for(; abs(b - a) > eps; iter_count++)
   {
      a1 = a, b1 = b;
      if(f1 < f2)
      {
         b = x2;
         x2 = x1;
         x1 = a + (3 - SQRT5) / 2 * (b - a);
         f2 = f1;
         f1 = funct(x + (x1)*Sk);
      }
      else
      {
         a = x1;
         x1 = x2;
         x2 = a + (SQRT5 - 1) / 2 * (b - a);
         f1 = f2;
         f2 = funct(x + (x2)*Sk);
      }
   }
   result =  a;
   return iter_count + f_calc_count;
}

// Поиск отрезка с максимумом функции
int FindSegmentWithMax(const double& delta, double funct(const vector<double>&),
                        const vector<double>& x, const vector<double>& Sk, double& a, double& b)
{
   double x0 = 0;
   double xk, xk1, xk_1, h = 2;
   double f = funct(x + (x0) * Sk);
   int f_calc_count = 1;

   if(f == funct(x + (x0 + delta) * Sk))
   {
      a = x0;
      b = x0 + delta;
      return 2;
   }
   else if(f == funct(x + (x0 - delta) * Sk))
   {
      a = x0 - delta;
      b = x0;
      return 3;
   }
   else
   {
      if(f > funct(x + (x0 + delta) * Sk))
      {
         xk = x0 - delta;
         h = -delta;
         f_calc_count++;
      }
      else if(f > funct(x + (x0 - delta) * Sk))
      {
         xk = x0 + delta;
         h = delta;
         f_calc_count += 2;
      }
      else
      {
         a = x0 - delta;
         b = x0 + delta;
         return f_calc_count + 2;
      }

      xk_1 = x0;

      bool exit = false;
      do
      {
         h *= 2;
         xk1 = xk + h;

         if(funct(x + (xk) * Sk) > funct(x + (xk1) * Sk))
         {
            xk_1 = xk;
            xk = xk1;
         }
         else
            exit = true;

         f_calc_count += 2;
      } while(!exit);

      a = xk_1;
      b = xk;
   }

   return f_calc_count;
}

// Поиск аргумента максимума функции вдоль направления методом золотого сечения
int FindMaxArgGolden(double funct(const vector<double>&),
                        const vector<double>& x, const vector<double>& Sk, const double& eps, double& result)
{
   double a = 0, b = 0;
   int f_calc_count = FindSegmentWithMax(0.1, funct, x, Sk, a, b);

   double x1 = a + (3 - SQRT5) / 2 * (b - a);
   double x2 = a + (SQRT5 - 1) / 2 * (b - a);
   double f1 = funct(x + (x1) * Sk);
   double f2 = funct(x + (x2) * Sk);
   double a1, b1;

   int iter_count = 0;
   for(; abs(b - a) > eps; iter_count++)
   {
      a1 = a, b1 = b;
      if(f1 > f2)
      {
         b = x2;
         x2 = x1;
         x1 = a + (3 - SQRT5) / 2 * (b - a);
         f2 = f1;
         f1 = funct(x + (x1) * Sk);
      }
      else
      {
         a = x1;
         x1 = x2;
         x2 = a + (SQRT5 - 1) / 2 * (b - a);
         f1 = f2;
         f2 = funct(x + (x2) * Sk);
      }
   }
   result = a;
   return iter_count + f_calc_count;
}