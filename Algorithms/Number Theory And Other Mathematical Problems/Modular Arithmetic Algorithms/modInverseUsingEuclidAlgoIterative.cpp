/*
 Find the modular multiplicative inverse of  a (mod m)
 USE Extended Euclidean Algorithm (Iterative)
 T = O(Log(m))
*/

#include <iostream>

using namespace std;

//Finds modular multiplicative inverse of  a (mod m)
//Using Iterative Approach
int modular_inverse(int a, int m)
{
    int m0 = m;
    int y = 0, x = 1;

    int q, temp; // q = quotient

    if(m == 1)
     return 0;

    while(a > 1)
    {
      q = a/m;
      temp = m;

      //Update a and m
      m = a%m , a = temp;
      temp = y;

      //Update x and y
      y = x - q*y;
      x = temp;
    }
   
   //Make x +ve
   if(x < 0)
     x += m0;

  return x;
}

int main()
{
    int a = 5;
    int m = 7;
    int result = modular_inverse(a, m);
    cout<<"modular_inverse("<<a<<", "<<m<<") = "<<result;
    return 0;
}
