#pragma once
#include <vector>
#include "Lab2Data.h"
#include "Vector.h"

class DanPshen
{
public:

   const int size;            // ����������� �������

   vector<double> Sk;         // ����� �������� �� ������� ����

   vector<double> xk;         // ����������� �� ������� ����
   vector<double> xk1;        // ����� �����������

   vector<double> grad_xk1;   // ��������������� ������ ��� ���������� ����������
   vector<double> t;          // ��������������� ������ ��� ���������� ���������
   
   int f_calc_count = 0;      // ����� ���������� �������

   DanPshen() : size(0)
   {

   }

   DanPshen(const int& t_size) : size(t_size)
   {
      Sk.resize(size);

      xk.resize(size);
      xk1.resize(size);

      grad_xk1.resize(size);
      t.resize(size);
   }

   int FindExtremum(double funct(const vector<double>&),
                    int min_max(double f(const vector<double>&), const vector<double>&, const vector<double>&, const double&, double&),
                    const vector<double>& x0,
                    const double& f_eps, const double& xs_eps, const double& grad_eps,
                    ofstream& fout)
   {
      f_calc_count = 0;
      // 1. ������ ��������� ������� f � ����� x0
      CalcGrad(funct, x0, Sk, grad_eps);
      f_calc_count += 4;
      Sk *= -1;
      xk = x0;

      fout << setw(3) << "k";
      fout << setw(14) << "x" << setw(14) << "y" << setw(14) << "f(x, y)";
      fout << setw(14) << "Sx" << setw(14) << "Sy" << setw(14) << "lambda";
      fout << setw(14) << "|xk - x(k-1)|" << setw(14) << "|yk - y(k-1)|" << setw(14) << "|fk - f(k-1)|";
      fout << setw(14) << "angle" << endl;

      bool exit_flag;
      int iter_count = 0;
      do
      {
         // 2. ����������� ������� f �� ����������� Sk
         //Function to_minimize = Function(xk, Sk);
         double lambda;
         f_calc_count += min_max(funct, xk, Sk, 1e-15, lambda) + 1;

         // ��������� ������ �����������
         xk1 = xk + lambda * Sk;

         // ���� ������
         fout << fixed << setw(3) << iter_count + 1;
         fout << scientific;
         fout << setw(14) << xk1[0] << setw(14) << xk1[1] << setw(14) << funct(xk1);
         fout << setw(14) << Sk[0] << setw(14) << Sk[1] << setw(14) << lambda;
         fout << setw(14) << abs(xk1[0] - xk[0]) << setw(14) << abs(xk1[1] - xk[1]) << setw(14) << funct(xk1) - funct(xk);
         fout << setw(14) << acos((xk1[0] * Sk[0] + xk1[1] * Sk[1]) / (Norm(xk1) * Norm(Sk))) * 180 / PI << endl;

         // 3. ���������� grad(f(xk1)) � �������� ������������ omega
         CalcGrad(funct, xk1, grad_xk1, grad_eps);
         f_calc_count += 4;
         //gradf1(xk1, grad_xk1);

         //double omega = (grad_xk1 * (grad_xk1 + Sk)) / (-1 * (Sk * Sk));
         double omega = (grad_xk1 * grad_xk1) / (Sk * Sk);

         // 4. ����������� ����� ����������� Sk1
         Sk = -1 * grad_xk1 + omega * Sk;

         // ������ ��������� ������� �� ������� ��������
         exit_flag = true;

         for(int i = 0; i < size; i++)
            if(abs(xk[i] - xk1[i]) > xs_eps)
               exit_flag = false;

         xk = xk1;

         iter_count++;

      } while(Norm(Sk) > f_eps && iter_count < 100 && exit_flag == false);
      fout << endl;

      return iter_count;
   }

   void CalcGrad(double funct(const vector<double>&), const vector<double>& point, vector<double>& res, const double& grad_eps)
   {
      for(int i = 0; i < size; i++)
      {
         t = point;
         t[i] += grad_eps;
         res[i] = funct(t);
         t[i] = point[i] - grad_eps;
         res[i] -= funct(t);
         res[i] /= 2.0 * grad_eps;
      }
   }
};
