#pragma once
#include <cmath>
#include <vector>

using namespace std;

const double SQRT5 = sqrt(5);

// Функция поиска минимум функции методом золотого сечения
double golden_ratio(vector<double> funct(vector<double>), double a, double b,
   const double& eps)
{
   double x1 = a + (3 - SQRT5) / 2 * (b - a);
   double x2 = a + (SQRT5 - 1) / 2 * (b - a);
   double f1, f2, a1, b1;

   int n = 0;
   for(; abs(b - a) > eps; n++)
   {
      f1 = funct(x1), f2 = funct(x2);
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