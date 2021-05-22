// Floor of square root of a number

#include<iostream>

using namespace std;

int floorSquareRoot(int number)
{
    if(number == 0 || number == 1)
      return number;
    
    //NOTE : floor of square root is always <= number/2 
    int start = 1, end = number/2;
    int result, mid;

    while(start <= end)
    {
       mid = (start + end)/2; 

       if(mid*mid == number) 
        return mid;

       if(mid*mid < number)
       {
           start = mid +1;
           result = mid; // floor of square root 
       } 
       else
           end = mid-1;
    }

    return result;
}

int main()
{
    int number = 35;
    cout<<"\nfloorSquareRoot("<<number<<") = "<<floorSquareRoot(number);
    return 0;
}