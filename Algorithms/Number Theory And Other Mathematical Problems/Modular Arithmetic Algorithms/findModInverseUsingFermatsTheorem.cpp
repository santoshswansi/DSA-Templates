// Find modular inverse of a (mod n)
// b can be called moddular inverse of a (mod n) if 
//         a * b = 1 (modn)

// Fermat's Theorem : 
// For prime 'p' and 'a' is not divisable by 'p' => (a, p) : co-prime
// Then a^(p-1) - 1 is integer multiple of 'p
//       OR
// a^(p-1) is congruent to 1 (mod p)    AND   'a' = [2, p-2]    

#include<iostream>
#include<numeric>

using namespace std;

//To calculate : ( x^y ) % z 
int modular_power(int x, int y, int z)
{
   if(y == 0)
     return 1;

   int p = modular_power(x, y/2, z)%z;

   p = (p*p)%z;

   return (y%2 == 0)? p : (p*x)%z;  
}

//To return GCD of two numbers //Eucledian algorithm for finding GCD
int gcd(int a, int b)
{
    if(a<b)
     return gcd(b, a);
    else if (b == 0)
     return a;
    return gcd(b, a%b);   
}

//To find modular inverse of a (mod p)
void modularInverse(int a, int p)
{
    //Check if they are co-prime OR not
    if(gcd(a, p) != 1)
        cout<<"\nInverse does not exist";

    else
    {   // (a, p) : co-prime 
        cout<<"\nModular Multiplicative Inverse of "<<a<<" ( mod "<<p<<" )"
            <<" is "<<modular_power(a, p-2, p); 
    }
      
}

int main()
{
    int a = 2, p = 17;
    modularInverse(a, p); 
    return 0;
}