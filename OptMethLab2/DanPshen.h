#pragma once
#include <vector>
#include "Function.h"
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
   vector<double> t;          // ��������������� ������ ��� ���������� ���������

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
      t.resize(size);
   }

   int FindExtremum(double f(const vector<double>&), const vector<double>& x0, const double& eps, const double& grad_eps)
   {
      // 1. ������ ��������� ������� f � ����� xk
      CalcGrad(f, x0, Sk, grad_eps);

      Sk *= -1;

      xk = x0;

      int iter_count = 0;
      do
      {
         // 2. ����������� ������� f �� ����������� Sk
         Function to_minimize = Function(xk, Sk);
         double lambda = to_minimize.FindMinArg(f, 1e-14);

         // ��������� ������ �����������
         xk1 = xk + lambda * Sk;

         // 3. ���������� grad(f(xk1)) � �������� ������������ omega
         CalcGrad(f, xk1, grad_xk1, grad_eps);

         //double omega = (-1 * Sk * (-1 * Sk - grad_xk1)) / (grad_xk1 *(-1 * Sk));
         double omega = (grad_xk1 * grad_xk1) / (Sk * Sk);

         // 4. ����������� ����� ����������� Sk1
         Sk = -1 * grad_xk1 + omega * Sk;

         xk = xk1;
         iter_count++;
      } while(Norm(Sk) > eps && iter_count < 2);

      return iter_count;
   }


   void CalcGrad(double funct(const vector<double>&), const vector<double>& point, vector<double>& res, const double& grad_eps)
   {
      for(int i = 0; i < size; i++)
      {
         t = point;

         res[i] = -funct(t);
         t[i] += grad_eps;
         res[i] += funct(t);
         res[i] /= grad_eps;
      }
   }
};
