// Primality Test Using Miller-Rabin algorithm

#include<iostream>

using namespace std;

int modular_power(int x, int y, int z)
{
    if(y == 0)
      return 1;

    int p = modular_power(x, y/2, z)%z;

    p =(p*p)%z;

    return (y%2==0)? p : (p*x)%z;  
}

//Return FALSE if num is composite 
//Return TRUE if num is probably prime
bool millerRabinTest(int num, int d)
{
   //Pick a random number 'a' in range [2, num-2]
   int a = 2 + rand()%(num-4);

   //Compute a^d % num
   int x = modular_power(a, d, num);

   if(x==1 || x == num-1)
     return true;

   //Keep squaring 'x' until one of the following does not happen
   // 1.) d == num-1
   // 2.) x^2 % num is not 1
   // 3.) x^2 % num is not (num-1)
   while(d != (num-1))
   {
       x = (x*x)%num;
       d*=2;

       if(x == 1)
        return false;
       if(x == num-1)
        return true; 
   }  
   return false; //Return composite 
}

// Find whether given number is prime OR not
// k = accuracy parameter (Larger k --> Higher accuracy)
bool isPrime(int num, int k)
{
  //Corner cases
  if(num <= 1 || num == 4)
    return false;

  if(num <= 3)
    return true;

  // Find 'd' such that (n-1) = d * 2^r  such that r >= 1
  int d = num-1;
  while(d%2 == 0)
    d/=2;

  //Call millerRabinTest k times
  for(int i = 0; i<k; ++i)
    if (!millerRabinTest(num, d))
      return false;

  return true;        
}

int main()
{
    int num = 2;
    int k = 4;
    cout << "isPrime(" << num << ") = " << isPrime(num, k) << endl;

    num = 8;
    cout << "isPrime(" << num << ") = " << isPrime(num, k) << endl;

    num = 23;
    cout << "isPrime(" << num << ") = " << isPrime(num, k) << endl;

    return 0;
}