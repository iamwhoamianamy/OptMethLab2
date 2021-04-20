#include <iostream>
#include <vector>
#include <iomanip>
#include "DanPshen.h"
#include "Newton.h"

using namespace std;

int main()
{
   vector<double> x0 = { 0.5, 2 };
   ofstream _f("f.txt");
   ofstream fout;

   DanPshen dp(2);

   //// Метод Данилина-Пшеничного
   //// На первой функции
   //fout = ofstream("results/f1_pshen.txt");
   //fout << setw(5) << "x0" << setw(5) << "y0" << setw(14) << "precision" << setw(14) << "iterations";
   //fout << setw(14) << "func. calc" << setw(14) << "x" << setw(14) << "y" << setw(14) << "f" << endl;
   //for(int i = -3; i >= -7 ; i--)
   //{
   //   int iter_count = dp.FindExtremum(f1, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), _f);
   //   fout << setw(5) << x0[0] << setw(5) << x0[1] << setw(12) << "10e" << i << setw(14) << iter_count << setw(14) << dp.f_calc_count;
   //   fout << scientific << setw(14) << dp.xk[0] << setw(14) << dp.xk[1] << setw(14) << f1(dp.xk) << defaultfloat << endl;
   //}
   //fout.close();

   //// На второй функции
   //fout = ofstream("results/f2_pshen.txt");
   //fout << setw(5) << "x0" << setw(5) << "y0" << setw(14) << "precision" << setw(14) << "iterations";
   //fout << setw(14) << "func. calc" << setw(14) << "x" << setw(14) << "y" << setw(14) << "f" << endl;
   //for(int i = -3; i >= -7; i--)
   //{
   //   int iter_count = dp.FindExtremum(f2, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -10), _f);
   //   fout << setw(5) << x0[0] << setw(5) << x0[1] << setw(12) << "10e" << i << setw(14) << iter_count << setw(14) << dp.f_calc_count;
   //   fout << scientific << setw(14) << dp.xk[0] << setw(14) << dp.xk[1] << setw(14) << f2(dp.xk) << defaultfloat << endl;
   //}
   //fout.close();

   //// На третьей функции
   //fout = ofstream("results/f3_pshen.txt");
   //fout << setw(5) << "x0" << setw(5) << "y0" << setw(14) << "precision" << setw(14) << "iterations";
   //fout << setw(14) << "func. calc" << setw(14) << "x" << setw(14) << "y" << setw(14) << "f" << endl;
   //for(int i = -3; i >= -7; i--)
   //{
   //   int iter_count = dp.FindExtremum(neg_f3, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), _f);
   //   fout << setw(5) << x0[0] << setw(5) << x0[1] << setw(12) << "10e" << i << setw(14) << iter_count << setw(14) << dp.f_calc_count;
   //   fout << scientific << setw(14) << dp.xk[0] << setw(14) << dp.xk[1] << setw(14) << f3(dp.xk) << defaultfloat << endl;
   //}
   //fout.close();

   Newton nt;

   //// Метод Ньютона
   //// На первой функции
   //fout = ofstream("results/f1_newton.txt");
   //fout << setw(5) << "x0" << setw(5) << "y0" << setw(14) << "precision" << setw(14) << "iterations";
   //fout << setw(14) << "func. calc" << setw(14) << "x" << setw(14) << "y" << setw(14) << "f" << endl;
   //for(int i = -3; i >= -7; i--)
   //{
   //   int iter_count = nt.FindExtremum(f1, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), _f);
   //   fout << setw(5) << x0[0] << setw(5) << x0[1] << setw(12) << "10e" << i << setw(14) << iter_count << setw(14) << nt.f_calc_count;
   //   fout << scientific << setw(14) << nt.xk[0] << setw(14) << nt.xk[1] << setw(14) << f1(nt.xk) << defaultfloat << endl;
   //}
   //fout.close();

   ////// На второй функции
   //fout = ofstream("results/f2_newton.txt");
   //fout << setw(5) << "x0" << setw(5) << "y0" << setw(14) << "precision" << setw(14) << "iterations";
   //fout << setw(14) << "func. calc" << setw(14) << "x" << setw(14) << "y" << setw(14) << "f" << endl;
   //for(int i = -3; i >= -7; i--)
   //{
   //   int iter_count = nt.FindExtremum(f2, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -10), _f);
   //   fout << setw(5) << x0[0] << setw(5) << x0[1] << setw(12) << "10e" << i << setw(14) << iter_count << setw(14) << nt.f_calc_count;
   //   fout << scientific << setw(14) << nt.xk[0] << setw(14) << nt.xk[1] << setw(14) << f2(nt.xk) << defaultfloat << endl;
   //}
   //fout.close();

   ////// На третьей функции
   //fout = ofstream("results/f3_newton.txt");
   //fout << setw(5) << "x0" << setw(5) << "y0" << setw(14) << "precision" << setw(14) << "iterations";
   //fout << setw(14) << "func. calc" << setw(14) << "x" << setw(14) << "y" << setw(14) << "f" << endl;
   //for(int i = -3; i >= -7; i--)
   //{
   //   int iter_count = nt.FindExtremum(neg_f3, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), _f);
   //   fout << setw(5) << x0[0] << setw(5) << x0[1] << setw(12) << "10e" << i << setw(14) << iter_count << setw(14) << nt.f_calc_count;
   //   fout << scientific << setw(14) << nt.xk[0] << setw(14) << nt.xk[1] << setw(14) << f3(nt.xk) << defaultfloat << endl;
   //}
   //fout.close();

   //_f.close();

   //// Метод Данилина-Пшеничного
   fout = ofstream("results/table.txt");
   fout << "Method: Danilin-Pshenichniy" << endl;
   fout << "f1" << endl;
   dp.FindExtremum(f1, FindMinArgGolden, x0, 0.001, 0.001, pow(10, -1), fout);
   fout << "f2" << endl;
   dp.FindExtremum(f2, FindMinArgGolden, x0, 0.001, 0.001, pow(10, -10), fout);
   fout << "f3" << endl;
   dp.FindExtremum(neg_f3, FindMinArgGolden, x0, 0.001, 0.001, pow(10, -1), fout);

   //// Метод Ньютона
   //fout << "Method: Newton" << endl;
   //fout << "f1" << endl;
   //nt.FindExtremum(f1, FindMinArgGolden, x0, 0.001, 0.001, pow(10, -1), fout);
   //fout << "f2" << endl;
   //nt.FindExtremum(f2, FindMinArgGolden, x0, 0.001, 0.001, pow(10, -10), fout);
   //fout << "f3" << endl;
   //nt.FindExtremum(neg_f3, FindMinArgGolden, x0, 0.001, 0.001, pow(10, -1), fout);
   //fout.close();
}