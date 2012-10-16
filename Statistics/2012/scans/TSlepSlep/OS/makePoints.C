#include <string>
#include <iostream>
#include <fstream>
using namespace std;

void makePoints ()
{
  ofstream outFile ("combined.out");
  for (int m1 = 100; m1 <= 300; m1 += 25) {
    for (int m2 = 0; m2 <= m1-25; m2 += 25) {
      outFile << m1 << ':' << m2 << " cls: 5.50867 8.87991 ( 6.00641 : 13.1059 )  ( 4.76288 : 17.6292 )" << endl;
    }
  }
}
