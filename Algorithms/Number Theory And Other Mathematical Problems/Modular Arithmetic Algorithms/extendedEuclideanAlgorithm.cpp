//Extended Euclidean Algorithm for GCD
// express gcd(a,b) = a.x  + b.y

#include<iostream>

using namespace std;

//Recursive method of finding GCD
int gcd(int a, int b, int *x, int *y)
{
    if(a == 0)
    {
        *x = 0;
        *y = 1;
        return b;
    }

    int x1, y1; //For storing result of recursive call
    int g  = gcd(b%a, a, &x1, &y1);

    //Update value of x and y
    *x = y1 - (b/a)*x1;
    *y = x1;

    return g;
}

int main()
{

    int a = 49, b = 21;
    int x, y;

    int result = gcd(a, b, &x, &y);

    cout << "GCD(" << a << ", " << b << ") = " << result << endl;
    cout << "GCD(" << a << ", " << b << ") = " <<a<<"."<<x<<" + "<<b<<"."<<y<<endl; 

    return 0;
}