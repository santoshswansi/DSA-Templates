// Find GCD of two numbers using Euclidean Algorithms 
// T = O(Log(min(a, b)))

#include<iostream>

using namespace std;

int gcd(int a, int b)
{
    if(a == 0)
     return b;
    return gcd(b%a, a); 
}

int main()
{
    int a = 49, b = 21;
    cout<<"GCD("<<a<<", "<<b<<") = "<<gcd(a,b)<<endl; 
    return 0;
}