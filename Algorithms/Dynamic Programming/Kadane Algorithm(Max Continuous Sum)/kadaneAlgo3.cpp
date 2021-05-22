//Find the max continuous sum of a given array
//T = O(n)

//This algorithm is valid also when all elements are negative

#include <iostream>
#include <algorithm>

using namespace std;

int kadaneAlgo(int array[], int size)
{
    int maxEndingHere = array[0]; // max continuous sum ending at current node
    int maxSoFar = array[0];      // max continuous sum calculated so far
    for (int i = 1; i < size; ++i)
    {
        //update maximum sum of sum-array ending at index 'i'
        maxEndingHere = maxEndingHere + array[i];
        
        //maximum sum should be greater than current element
        maxEndingHere = max(maxEndingHere, array[i]);

        //Update the result
        if (maxEndingHere > maxSoFar)
            maxSoFar = maxEndingHere;
    }
    return maxSoFar;
}

int main()
{
    int array[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    int size = sizeof(array) / sizeof(array[0]);
    cout << "\nMax sub-array sum = " << kadaneAlgo(array, size);

    int array1[] = {-8, -3, -6, -2, -5, -4};
    size = sizeof(array1)/sizeof(array1[0]);
    cout << "\nMax sub-array sum = " << kadaneAlgo(array1, size);

    return 0;
}