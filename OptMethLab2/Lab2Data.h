#pragma once
#include <vector>
using namespace std;

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
