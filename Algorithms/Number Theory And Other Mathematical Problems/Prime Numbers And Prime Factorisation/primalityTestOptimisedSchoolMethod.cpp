// Given a number you have been asked to answer whether the number
// is prime OR not

//IDEA : Every prime number can be expressed in the form : 6k +/- 1
//       (Except 2 AND 3)
//NOTE : There are also composite numbers which can be expressed by this

#include<iostream>

using namespace std;

bool isPrime(int num)
{
  if(num == 2 || num == 3)
    return true;

  if(num%2 == 0 || num%3 == 0)
   return false;   

  for(int i = 5; i*i <= num; i+=6)
  {
      if(num%(i+0) == 0 || num%(i+2) == 0)
        return false;
  }
  return true;
}

int main()
{
    int num = 2;
    cout<<"isPrime("<<num<<") = "<<isPrime(num)<<endl;

    num = 8;
    cout<<"isPrime("<<num<< ") = "<<isPrime(num)<<endl;

    num = 23;
    cout<<"isPrime("<<num<< ") = "<<isPrime(num)<<endl;

    return 0;
}