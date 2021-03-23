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

  /* void FindSegmentWithMin(double x0, const double& DELTA,
      double funct(double), const std::string& OUT_FILE)
   {
      int k = 1;
      double xk, xk1, xk_1, h;

      std::ofstream fout(OUT_FILE);
      fout << "    i            xi         f(xi)" << std::endl;
      fout << std::fixed << std::setw(5) << k;
      fout << std::scientific;
      fout << std::setw(14) << x0 << std::setw(14) << funct(x0);
      fout << std::endl;

      double f = funct(x0);
      if(f == funct(x0 + DELTA))
         fout << "segment with minimum: [" << x0 << ";" << x0 + DELTA << "]";
      else if(f == funct(x0 - DELTA))
         fout << "segment with minimum: [" << x0 << ";" << x0 - DELTA << "]";
      else
      {
         if(f > funct(x0 + DELTA))
         {
            xk = x0 + DELTA;
            h = DELTA;
         }
         else if(f > funct(x0 - DELTA))
         {
            xk = x0 - DELTA;
            h = -DELTA;
         }

         xk_1 = x0;

         bool exit = false;
         do
         {

            h *= 2;
            xk1 = xk + h;

            if(funct(xk) > funct(xk1))
            {
               xk_1 = xk;
               xk = xk1;
               k++;

               fout << std::fixed << std::setw(5) << k;
               fout << std::scientific;
               fout << std::setw(14) << xk << std::setw(14) << funct(xk);
               fout << std::endl;
            }
            else
               exit = true;
         } while(!exit);

         fout << "segment with minimum: [" << xk_1 << ";" << xk1 << "]";
      }
      fout.close();
   }*/
};