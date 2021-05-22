// Find nCr % p using Fermat's Little Theorem AND 
// CONDITION: { p is prime number > n }

// nCr % p = fact(n)*modInverse(fact(r))*modInverse(fact(n-r))%p 

#include<iostream>
#include<vector>

using namespace std;

// Find a^b % c 
int modular_power(int a, int b, int c)
{
  int result = 1;

  //Update a if a>=c
  //Because  a^b % c = (a%c)^b % c
   a = a%c; 

  while(b > 0)
  {
    // b : odd
    if(b & 1)
      result = (result*a)%c;

    b = b >> 1; //b = b/2
    a = (a*a) % c;  
  } 
  return result;
}

// Returns modular multiplicative inverse of a % p
int modInverse(int a, int p)
{
    return modular_power(a, p-2, p);
}

//Returns nCr % p (Using Fermat's Little Theorem)
int nCrModpUsingFermat(int n, int r, int p)
{
   if(r == 0)
    return 1;

   //Fill factorial array till the  upper limit 'n'
   vector<int> fact(n+1);

   fact[0] = 1;
   for(int i = 1; i <= n; ++i)
     fact[i] = (fact[i-1]*i)%p;

  //Return the result using the formula
  return (fact[n] * ( modInverse(fact[r], p)%p ) *
                    ( modInverse(fact[n-r], p)%p) )%p;
}

int main()
{
    // CONDITION : ( p = prime number > n )
    int n = 10, r = 2, p = 13;
    cout << "C(" << n << ", " << r << ", " << p << " ) = " << nCrModpUsingFermat(n, r, p);
    return 0;
}