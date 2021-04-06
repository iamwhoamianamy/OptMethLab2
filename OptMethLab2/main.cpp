#include <iostream>
#include <vector>
#include <iomanip>
#include "DanPshen.h"
#include "Newton.h"

using namespace std;


int main()
{
   vector<double> x0 = { 2, 5 };
   ofstream fout;

   DanPshen dp(2);

   // Метод Данилина-Пшеничного
   // На первой функции
   fout = ofstream("results/f1_pshen.txt");
   for(int i = -3; i >= -7 ; i--)
      dp.FindExtremum(f1, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), fout);
   fout.close();

   // На второй функции
   fout = ofstream("results/f2_pshen.txt");
   for(int i = -3; i >= -7; i--)
      dp.FindExtremum(f2, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -10), fout);
   fout.close();

   // На третьей функции
   fout = ofstream("results/f3_pshen.txt");
   for(int i = -3; i >= -7; i--)
      dp.FindExtremum(f3, FindMaxArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), fout);
   fout.close();

   Newton nt;

   // Метод Ньютона
   // На первой функции
   fout = ofstream("results/f1_newton.txt");
   for(int i = -3; i >= -7; i--)
      nt.FindExtremum(f1, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), fout);
   fout.close();

   //// На второй функции
   fout = ofstream("results/f2_newton.txt");
   for(int i = -3; i >= -7; i--)
      nt.FindExtremum(f2, FindMinArgGolden, x0, pow(10, i), pow(10, i), pow(10, -10), fout);
   fout.close();

   //// На третьей функции
   fout = ofstream("results/f3_newton.txt");
   for(int i = -3; i >= -7; i--)
      nt.FindExtremum(f3, FindMaxArgGolden, x0, pow(10, i), pow(10, i), pow(10, -1), fout);
   fout.close();


   int asd = 1111;
   
}