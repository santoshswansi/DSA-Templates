// Find n-th fib-series using a formula
//  F(n) = round( pow((root(5) + 1)/2, n )/root(5)

#include<iostream>
#include<math.h>

using namespace std;

int fib(int n)
{
    return round(pow((sqrt(5) + 1)/2, n) / sqrt(5)); 
}

int main()
{
    int n = 10;
    cout << "fib(" << n << ") = " << fib(n) << endl;
    return 0;
}