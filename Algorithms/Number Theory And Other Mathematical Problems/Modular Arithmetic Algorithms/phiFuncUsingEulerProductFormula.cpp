//Find phi function using Euler product Formula
// EULER PRODUCT FORMULA :
// phi(n) = n * (1 - 1/p)  , where p are prime fators of n

#include<iostream>

using namespace std;

//Euler Product Formula based phi function
int phi(int n)
{
   float result = n;
   for(int i = 2; i*i <= n; ++i)
   {
       //If 'i' is prime
       if(n%i == 0)
       {
           //Remove all occurrences of 'i' in 'n'
           while(n%i == 0)
             n/=i;
           result*= (1.0 - (1.0/(float)i));  
       }
   } 

   // If n has a prime factor > root(n)
   if(n > 1)
     result*= (1.0 -(1.0/(float)n));

   return (int)result;  
}

int main()
{
    int n = 10;
    cout<<"phi("<<n<<") = "<<phi(n)<<endl;

    // n : prime
    n = 23;
    cout << "phi(" << n << ") = " << phi(n)<<endl;
    
    return 0;
}