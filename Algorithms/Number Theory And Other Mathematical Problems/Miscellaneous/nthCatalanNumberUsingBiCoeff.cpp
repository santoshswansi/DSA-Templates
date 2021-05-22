//Using binomial coefficient find the nth Catalan nummber

#include<iostream>

using namespace std;

unsigned long int binomialCoeff(int n, int r)
{
    unsigned long int result = 1;

    //Optimisation 
    if(r > n-r) 
      r = n-r;

    for(int i = 0; i < r; ++i)
    {
       result*= (n-i);
       result/= (i+1);
    }  
    return result;
}

unsigned long int nthCatalanNumber(unsigned int number)
{
    unsigned long int c = binomialCoeff(2*number, number);
    return c/(number + 1);
}

int main()
{
    int number = 7;
    cout << number << "th Catalan Number = " << nthCatalanNumber(number);
    return 0;
}