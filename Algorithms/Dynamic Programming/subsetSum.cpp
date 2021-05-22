// Find whether there is a subset of a given set whose sum of elements 
//is equal to given sum 

#include<iostream>

using namespace std;

//To find the subset with required sum
bool isSubsetSum(int set[], int  size, int sum)
{
    //Table
    //subset[i][j] = stores T/F value for set[0...i-1] with sum = "sum"
    int **subset = new int*[size+1];

    // allocate memory for all pointers of subset (columns)
    for(int i = 0; i <size+1; ++i)  
     subset[i] = new int[sum+1];

    // sum = 0 ( TRUE ---> Empty set)
    for(int i = 0; i <= size; ++i)
     subset[i][0] = true; 

    // sum != 0 AND set = empty ----> Sum Not Possible ( FALSE )
    for(int i  = 1; i <= size; ++i)
     subset[0][i] = false;

    for(int lastPos = 1; lastPos <= size; ++lastPos)
    {
        for(int currSum = 1; currSum <= sum; ++currSum)
        {
           // If ( value_of_last_element ) > (current sum)
           // Does not include it
           // Else
           // Either include it OR exclude it
           if( currSum < set[lastPos-1])
              subset[lastPos][currSum] = subset[lastPos-1][currSum];
           else 
              subset[lastPos][currSum] = subset[lastPos-1][currSum] ||
                                         subset[lastPos-1][currSum-set[lastPos-1]] ;    
        }
    }
    return subset[size][sum];
}

int main()
{
    int set[] = {3, 34, 4, 12, 5, 2};
    int size = sizeof(set)/sizeof(set[0]);
    int sum = 9;
    if(isSubsetSum(set, size, sum))
      cout<<"\nSubset sum of 9 is possible.";   
    else
      cout<<"\nSubset sum of 9 is not possible";
    return 0;
}