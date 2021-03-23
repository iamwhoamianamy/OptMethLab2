#pragma once
#include <vector>
#include "GoldenRatio.h"
#include "Vector.h"

class DanPshen
{
public:

   const int size;            // ����������� �������

   vector<double> Sk;         // ����� �������� �� ������� ����
   vector<double> Sk1;        // ����� �������� �� ������ �����������

   vector<double> xk;         // ����������� �� ������� ����
   vector<double> xk1;        // ����� �����������

   vector<double> grad_xk1;   // ��������������� ������ ��� ���������� ����������

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
      // 1. ������ ��������� ������� f � ����� xk
      CalcGrad(f, x0, Sk);

      Sk *= -1;

      xk = x0;

      int k = 0;
      do
      {
         // 2. ����������� ������� f �� ����������� Sk
         Function to_minimize = Function(xk, Sk);
         double lambda = to_minimize.FindMinArg(f, eps);

         // ��������� ������ �����������
         xk1 = xk + lambda * Sk;

         // 3. ���������� grad(f(xk1)) � �������� ������������ omega

         CalcGrad(f, xk1, grad_xk1);
         //grad_xk1 *= -1;

         //double omega = (-1 * Sk * (-1 * Sk - grad_xk1)) / (grad_xk1 *(-1 * Sk));
         double omega = (grad_xk1 * grad_xk1) / (Sk * Sk);

         // 4. ����������� ����� ����������� Sk1
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
