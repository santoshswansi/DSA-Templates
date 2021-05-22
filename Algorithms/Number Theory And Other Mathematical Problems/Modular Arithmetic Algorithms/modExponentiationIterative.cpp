// Find a^b (mod c)
// T = O(Log(b))
// Iterative Implementation

#include<iostream>

using namespace std;

int modular_power(int a, int b, int c)
{
    int result = 1;

    //Update a if ( a >= c )
    a = a%c;

    if(a == 0) //If x is divisible by c 
     return 0;

    while(b > 0)
    {
        // b = odd
        if( b & 1)
         result = (result*a)%c;

        // b must be even now
        b = b >> 1;   // b = b/2
        result = (result * result)%c; 
    } 
   return result;
}

int main()
{
    int a = 3, b = 4, c = 6;
    cout << "modular_power(" << a << ", " << b << ", " << c << ") = " << modular_power(a, b, c);

    return 0;
}