#include <iostream>
#include <vector>
#include <iomanip>
#include "DanPshen.h"
#include "Function.h"
#include "Newton.h"

using namespace std;


int main()
{
   //for(int i = 5; i > -20; i--)
   {
      int i = -8;
      cout << fixed << "10e" << i << endl;

      vector<double> point = { 2, 5 };

      Newton newton;
      if(newton.FindMinimum(f1, point, 1e-14, pow(10, i)))
      {
         cout << "Newton: " << scientific << endl;
         cout << setw(16) << abs(newton.xk1[0] - 1) << " ";
         cout << setw(16) << abs(newton.xk1[1] - 1) << " " << endl;
      }
      DanPshen dp(2);
      int iters = dp.FindExtremum(f1, point, 1e-14, pow(10, i));

      cout << "Pshenichniy: " << fixed << iters << scientific << endl;
      cout << setw(16) << abs(dp.xk1[0] -1) << " ";
      cout << setw(16) << abs(dp.xk1[1] -1) << " ";

      cout << endl << endl;
   }
   

   int asd = 1111;
   
}