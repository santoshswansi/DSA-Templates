//Find the max continuous sum of a given array
//T = O(n)

//This algorithm is valid only when all elements are not negative

#include<iostream>
#include<algorithm>

using namespace std;

int kadaneAlgo(int array[], int size)
{
   int maxEndingHere = 0; // max continuous sum ending at current node
   int maxSoFar = 0; // max continuous sum calculated so far
   for(int i = 0; i < size; ++i)
   {
       //update maximum sum of sum-array ending at index 'i'
       maxEndingHere = maxEndingHere + array[i];
       
       //If max continuous sub-array sum ending at curr index= negative,
       // set the maxEndingHere to zero
       maxEndingHere = max(maxEndingHere, 0);

       //Update the result
       if(maxEndingHere > maxSoFar)
          maxSoFar = maxEndingHere;

   }
   return maxSoFar;
}

int main()
{
   int array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
   int size = sizeof(array)/sizeof(array[0]);
   cout<<"\nMax sub-array sum = "<<kadaneAlgo(array, size);
   return 0;
}