/*
Given a set of congruences with remainders = rem[] AND 
num[] . Find minimum x such that :-
            x % num[0] = rem[0]
            x % num[1] = rem[1]
            ...................
*/

#include<iostream>

using namespace std;

int findMinX(int rem[], int num[], int k)
{
    int x = 1;
    int i;

    //A/T Chinese Remainder Theorem loop will always break
    while(true)
    {
       for( i = 0; i<k; ++i)
          if(x%num[i] != rem[i])
            break;
   
       if(i == k)
         return x;
   
       //Update x       
       ++x;
    }  
    return x; 
}

int main()
{
    int rem[3] = {3, 1, 6};
    int num[3] = {5, 7, 8};
    int k = sizeof(rem)/sizeof(rem[0]);

    cout<<"Result = "<<findMinX(rem, num, k);

    return 0;
}