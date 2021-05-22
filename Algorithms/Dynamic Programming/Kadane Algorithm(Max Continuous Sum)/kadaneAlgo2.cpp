//Find the max continuous sum of a given array
//T = O(n)

//This algorithm is valid also when all elements are negative

#include <iostream>
#include <algorithm>

using namespace std;

int maxElem(int array[], int size)
{
    int max = array[0];
    for(int i = 1; i < size; ++i)
       if(array[i] > max)
         max = array[i];

    return max;       
}

int kadaneAlgo(int array[], int size)
{
    //To handle case when all elements are negative
    int maxElement = maxElem(array, size);

    if(maxElement < 0)
     return maxElement;

    int maxEndingHere = 0; // max continuous sum ending at current node
    int maxSoFar = 0;      // max continuous sum calculated so far
    for (int i = 0; i < size; ++i)
    {
        //update maximum sum of sum-array ending at index 'i'
        maxEndingHere = maxEndingHere + array[i];

        //If max continuous sub-array sum ending at curr index= negative,
        // set the maxEndingHere to zero
        maxEndingHere = max(maxEndingHere, 0);

        //Update the result
        if (maxEndingHere > maxSoFar)
            maxSoFar = maxEndingHere;
    }
    return maxSoFar;
}

int main()
{
    int array[] = {-8, -3, -6, -2, -5, -4};
    int size = sizeof(array) / sizeof(array[0]);
    cout << "\nMax sub-array sum = " << kadaneAlgo(array, size);
    return 0;
}