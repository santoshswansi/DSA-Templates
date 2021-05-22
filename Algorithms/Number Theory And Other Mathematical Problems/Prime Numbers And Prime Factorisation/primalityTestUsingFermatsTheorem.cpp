// Fermat's Theorem :
// For prime 'p' and 'a' is not divisable by 'p' => (a, p) : co-prime
// Then a^(p-1) - 1 is integer multiple of 'p'
//       OR
// a^(p-1) is congruent to 1 (mod p)    AND   'a' = [2, p-2]

//Probablistic method of primality test using Fermat's theorem
// T = O(kLog(n))

#include<iostream>

using namespace std;

//To calculate gcd using Eucledian Algorithm
int gcd(int a, int b)
{
    if(a<b)
      return gcd(b, a);
    else if(b == 0)
      return a;
    return gcd(b, a%b);    
}

//To calculate a^b % c
int modular_power(int a, int b, int c)
{
    if(b == 0)
     return 1;
   
    int p = modular_power(a, b/2, c)%c;

    p = (p*p)%c;

    return (b%2 == 0)? p : (p*a)%c;
}

// k = accuracy parameter
// Larger k --> Higher accuracy
bool isPrime(unsigned int num, int k)
{
  //Corner cases
  if(num <=1 || num == 4)
   return false;
  if(num <= 3)
   return true;

  while(k>0)
  {
      //Generate a random number 'a' = [2, num-2]
      //Above case make sure that num > 4
      int a = 2 + rand()%(num-4);

      // If (a, n) not coprime , RETURN false
      if(gcd(a,num) != 1)
        return false;

      //Fermat's theorem
      if(modular_power(a, num-1, num) != 1)
        return false;  

      --k;   
  }   
  return true;
}

int main()
{
    int num = 2;
    int k = 3;
    cout << "isPrime(" << num << ") = " << isPrime(num, k) << endl;

    num = 8;
    cout << "isPrime(" << num << ") = " << isPrime(num, k) << endl;

    num = 29;
    cout << "isPrime(" << num << ") = " << isPrime(num, k) << endl;

    return 0;
}
