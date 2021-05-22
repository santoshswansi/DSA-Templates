//Partition a set into two subsets such that absolute difference is 
//minimum

// T = O(n *sum)  n --> length of set , sum ---> sum of all elements

#include<iostream>
#include<climits>
#include<vector>

using namespace std;

int findMinDifference(int array[], int size)
{
    //Find the sum of all elements
    int sum = 0;
    for(int i = 0; i < size; ++i)
     sum += array[i];

    //To store results of sub-problem
    vector<vector<bool>> dp(size + 1, vector<bool> (sum+1, false));

    //Initialise 1st  column as 'true'
    // zero sum is possible with all elements
    for(int i = 0; i <= size; ++i)
       dp[i][0] = true;

    //Initialise 1st row as false(except dp[0][0])
    //(With zero elements no sum is possible except 0)   
    for(int i = 1; i <= sum; ++i)
       dp[0][i] = false;

    for(int i = 1; i <= size; ++i)  // For number of elements 
    {
        for(int j = 1; j <= sum ; ++j) //For sum
        {                       
           // i-th element excluded
           dp[i][j] = dp[i-1][j]; // Copy values from top

           if(array[i-1] <= j)    // i-th element included
             dp[i][j] = dp[i-1][j - array[i-1]];
              
        } 
    }

    int diff = INT_MAX; // Difference of two sums

    //Find the largest 'j' such that dp[n][j] is true 
    //Where j loops  from sum/2 to 0
    //NOTE : Looping from sum/2 is to make difference of sum of subsets 
    //       minimum
    for(int j = sum/2 ; j>=0 ; --j)
    {
        if(dp[size][j] == true)
        {
            diff = sum - 2*j;
            break;
        }
    }
    return diff;
}

int main()
{
    int array[] = {1,6,11,5};
    int size = sizeof(array)/sizeof(array[0]);
    cout<<"\nMinimum of difference of sum : "<<findMinDifference(array,size); 
    return 0;
}
