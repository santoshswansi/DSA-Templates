/*
Find the modular multiplicative inverse of  a (mod m)
USE Extended Euclidean Algorithm (Recursive)
T = O(Log(m))
*/

#include<iostream>

using namespace std;

// Extended euclidean algorithm for gcd (recursive)
int gcdExtended(int a, int b, int *x, int *y)
{
  if(a == 0)
  {
      *x = 0;
      *y = 1;
      return b;
  }

  int x1, y1; // To store values for recursive call
  int g = gcdExtended(b%a, a, &x1, &y1);

  //Update x and y
  *x = y1 - (b/a)*x1;
  *y = x1;
  
  return g;
}

void modular_inverse(int a, int m)
{
  int x, y;  
  int g = gcdExtended(a, m, &x, &y);

  //If a and m are not co-prime modular-inverse not possible
  if(g != 1)
    cout<<"Modular inverse does not exist"<<endl;
  else
  {
    //To handle -ve  value of x  
    int result = (x%m + m)%m;  
    cout<<"modular_inverse("<<a<<", "<<m<<") = "<<result;
  }
  
}

int main()
{
  int a = 5;
  int m = 7;
  modular_inverse(a, m);
  return 0;
}