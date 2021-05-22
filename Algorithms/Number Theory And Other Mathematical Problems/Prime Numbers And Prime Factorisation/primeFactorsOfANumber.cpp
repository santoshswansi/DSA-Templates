//Find all prime factors of a number

#include<iostream>

using namespace std;

void primeFactors(int num)
{
  //Print the number of 2s that divide
  while(num%2 == 0)
  {
      cout<<2<<" ";
      num /= 2;
  } 

  // n must be odd now, so we can skip one element
  for(int i = 3; i*i <= num; i+=2)
  {
      if(num%i == 0)
      {
          cout<<i<<" ";
          num/=i;
      }
  }

  //if num is prime (>2)
  if(num > 2)
   cout<<num<<" ";

}

int main()
{
    int num = 21;
    primeFactors(num);
    return 0;
}