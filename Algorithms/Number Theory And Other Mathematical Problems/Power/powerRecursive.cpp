//Find x to the power y (DP)
#include<iostream>

using namespace std;

int power(int x, int y)
{
    if(y==0)
       return 1;

    //We can avoid calculating power(x, y/2) multiple times by storing 
    //its result

    int temp = power(x, y/2);  

    if(y%2 == 0)
       return temp*temp;
    
    return x*temp*temp;  
}

int main()
{
    unsigned int x = 6;
    unsigned int y = 4;
    cout<<"power(6, 4) = "<<power(6, 4);
    return 0;
}