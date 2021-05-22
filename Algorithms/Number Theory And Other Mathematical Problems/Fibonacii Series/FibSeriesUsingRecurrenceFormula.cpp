// If n : EVEN then k = n/2
//   F(n) = 2*F(k-1) + F(k)*F(k)

// If n: ODD then k = (n+1)/2
//   F(n) = F(k)*F(k) + F(k-1)*F(k-1)

#include<iostream>

using namespace std;
#define MAX  1000

int f[MAX] = {0};

int fib(int n)
{
    if(n==0)
     return 0;
    if(n==1 || n==2) //first initialise then return it
     return (f[n] = 1);

    //if f(n) : already calculated
    if(f[n])
      return f[n];

    int k = (n & 1)? (n+1)/2 : n/2;

    f[n] = (n & 1) ? fib(k)*fib(k) + fib(k-1)* fib(k-1) :
                     2*fib(k-1)  + fib(k)*fib(k); 

    return f[n];                 
}

int main()
{
    int n = 5;
    cout<<"fib("<<n<<") = "<<fib(n)<<endl; 
    return 0;
}