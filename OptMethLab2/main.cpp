#include <iostream>
#include <vector>
#include <iomanip>
#include "DanPshen.h"
#include "Function.h"

using namespace std;

double f1(const vector<double>& x)
{
   return 100 * pow(x[1] - x[0], 2) + pow(1 - x[0], 2);
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
   double half_2 = A2 / (1 + brack_3 * brack_3 + brack_3 * brack_4);

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

int main()
{
   //for(int i = 10; i > -20; i--)
   //{
   //   DanPshen dp = DanPshen(2);
   //   vector<double> x0 = { 2 , 2 };
   //   vector<double> res(2);

   //   dp.CalcGrad(f1, x0, res, pow(10, i));

   //   cout << fixed << setw(4) << i;
   //   cout << scientific << setw(16) << abs(2.0 - res[0]) << " " << abs(0 - res[1]) << endl;
   //}

   DanPshen dp = DanPshen(2);
   vector<double> x0 = { 2 , 2 };
   vector<double> prec = { 1 , 1 };

   for(int i = 10; i > -20; i--)
   {
      int k = dp.FindExtremum(f1, x0, 1e-8, pow(10, i));

      cout << fixed << setw(4) << i;
      cout << scientific;
      //for(size_t i = 0; i < dp.xk.size(); i++)
      cout << setw(16) << abs(dp.xk[0] - prec[0]) << " ";
      cout << setw(16) << abs(dp.xk[1] - prec[1]) << " ";
      cout << Norm(dp.xk - prec);
      cout << endl;
   }

   int asd = 1111;
}