/*
Given a set of congruences with remainders = rem[] AND 
num[] . Find minimum x such that :-
            x % num[0] = rem[0]
            x % num[1] = rem[1]
            ...................
*/

//FORMULA 
// x =  summation of rem[i]*N[i]*X[i] % N   ,  0 <= i < k
// where, N    =  num[0]*num[1].....*num[k-1]
//        N[i] =  N/num[i]
//        X[i] =  modular inverse of N[i] (mod num[i])

#include <iostream>

using namespace std;

//To find multiplicative modular inverse of  a (mod m) 
// { Iterative approach of extended euclidean algorithm }
int modular_inverse(int a, int m)
{
    int m0 = m;
    int x = 1, y = 0;
    int temp, q; // quotient

    if(m == 1)
      return 0;

    while(a > 1)
    {
       q = a/m;

       //Update a & m
       temp = m;
       m = a%m, a = temp;

       //Update x and y
       temp = y;
       y = x - q*y;
       x = temp;
    }

    //Make x positive
    if(x < 0)
     x += m0;

   return x;  
}

int findMinX(int rem[], int num[], int k)
{
    int result =  0;
    
    int N = 1; // For num[0]*num[1]*num[2].....*num[k-1]
    int Ni; // For N/num[i]

    for(int i = 0; i<k; ++i)
      N*= num[i];

    for(int i = 0; i<k; ++i)
    {
        Ni = N / num[i]; //N/num[i]
        result = (result + rem[i] * Ni * modular_inverse(Ni, num[i]))%N;
    }
    return result;
}

int main()
{
    int rem[3] = {3, 1, 6};
    int num[3] = {5, 7, 8};
    int k = sizeof(rem) / sizeof(rem[0]);

    cout << "Result = " << findMinX(rem, num, k);

    return 0;
}