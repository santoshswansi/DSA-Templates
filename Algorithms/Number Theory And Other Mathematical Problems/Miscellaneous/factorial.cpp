//Find the factorial of a large number
#include<iostream>

using namespace std;
#define MAX 500

//Multiply x with res[]
void multiply(int x, int res[], int &resSize)
{
    int product;
    int carry = 0;
    for(int i = 0; i < resSize; ++i)
    {
       product = res[i]*x + carry;
       res[i] = product%10; //Store the last digit in res[]
       carry = product/10;  //Store the  remaining number in carry
    } 

    while (carry)
    {
       res[resSize] = carry%10;
       carry = carry/10;
       resSize++;
    }
}

void  factorial(int number)
{
   //It will store result in reverse order
   int res[MAX];

   res[0] = 1;
   int resSize = 1;

   for(int x = 2; x <= number; ++x)
   {
     multiply(x, res, resSize);
   }

   //Print the result
   cout<<"Factorial of "<<number<<" is ";
   for(int i=resSize-1; i>=0; --i)
     cout<<res[i];

}

int main()
{
    int number = 100;
    factorial(number);
    return 0;
}