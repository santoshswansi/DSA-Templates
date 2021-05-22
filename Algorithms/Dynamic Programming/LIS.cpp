//Find the Longest Increasing Sub-Sequence of an integer array
//Tabulated version of DP
// T = O(n^2)

#include<iostream>
#include<algorithm>

using namespace std;

int LIS(int array[], int size)
{
    int *lis  = new int[size];
    lis[0] = 1; 
    for(int len = 1; len<size; ++len)  // Loops for all possible length
    {
        //Initialise lis[len] = 1
        lis[len] = 1;
        for(int j = 0; j<len; ++j)
        {
            if(array[len] > array[j] && lis[len] < lis[j]+1)
             lis[len] = lis[j] + 1;
        }
    }

    return *max_element(lis, lis+size);
}

int main()
{
    int array[] = { 10 ,22, 9, 33, 21, 50, 41, 60, 80};
    int size = sizeof(array)/sizeof(array[0]);
    cout<<"\nLongest Increasing Sub-Sequence : "<<LIS(array, size);
    return 0;
}