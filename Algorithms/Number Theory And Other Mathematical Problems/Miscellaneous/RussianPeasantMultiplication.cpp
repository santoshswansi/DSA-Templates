#include<iostream>

using namespace std;

unsigned int russianPeasantMultiplication(unsigned int a, unsigned int b)
{
    int result = 0;
    while(b>0)
    {
       if(b & 1)
        result += a;

       a = a << 1;
       b = b >> 1;
    }
    return result;
}

int main()
{
    int a = 1200, b = 13;
    cout<<a<<"X"<<b<<" = "<<russianPeasantMultiplication(a, b)<<endl;
    return 0;
}