//Using pollard rho algorithm to find a prime divisor of a given number


#include<iostream>
#include<time.h>

using namespace std;

//Eucledian Algorithm for GCD
long long int gcd(long long int a, long long int b)
{
    if(a<b)
     return gcd(b, a);
    else if(b == 0)
     return a;
    
    return gcd(b, a%b);  
}

long long int modular_power(long long int x,
                            long long int y,
                            long long int z)
{
    if(y == 0)
     return 1;

    long long int p = modular_power(x, y/2,z)%z;

    p =(p*p)%z;
 
    return (y%2==0)? p : (p*x)%z;
}

long long int pollardRho(long long int num)
{
   //Initialise current time as seed to rand()
   srand(time(0));

   //No prime divisor for 1
   if(num == 1)
    return num;

   if(num%2 == 0)
    return 2;

  //Pick 'x' in range[2, N-1]
  long long int x = rand()%(num-2) + 2;      
  long long int y = x; //Initialise y with x

  //Calculate value of c in range [1, num-1]
  long long int c = rand()%(num-1) + 1;

  //d(Divisor) = 1 ----> result
  long long int d = 1;

  //While we have not got the divisor
  while(d == 1)
  {
      //Tortoise move :  x(i+1) = f(x(i))
      x = (modular_power(x, 2, num) + c)%num;

      //Hare move y(i+1) = f(f(y))
      y = (modular_power(y, 2, num) + c)%num;
      y = (modular_power(y, 2, num) + c)%num;

      //Find gcd of abs(x-y) and num 
      d = gcd(abs(x-y), num);

      //Retry if the algorithm fails to find prime factor of 
      //given number with different set of 'x' , 'y' and 'c'
      if(d==num) 
       return pollardRho(num);
  }
  return d; //return divisor
}

int main()
{
  long long int num = 10967535067;
  cout<<"Prime divisor of "<<num<<" is "<<pollardRho(num)<<endl;
  return 0;
}