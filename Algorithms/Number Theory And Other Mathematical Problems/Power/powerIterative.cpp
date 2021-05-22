//Iterative method of finding power(x,y)
// T = O(Log(y))
// Extra space = O(1)

//Recursive solutions are generally not preferred as they require 
//space on stack and function call overhead (indirect computation time)

#include<iostream>

using namespace std;

float power(float x, int y)
{
    float res = 1;
    if(y == 0)
       return 1;

    while(y > 0)
    {
        if(y & 1)
          res *= x;

        y = y>>1;  // y = y/2 
        x = x*x;  
    }   
    return res;
}

int main()
{
    float x = 2;
    int y = 5;
    cout<<"power(2, 5) = "<< power(x, y) << endl;

    return 0;
}

