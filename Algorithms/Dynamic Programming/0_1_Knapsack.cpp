// Given an array of items with their weights and values(profits)
// and a knapsack of fixed capacity 
// We need to put items in the knapsack so that sum of their values 
// would be maximum (weight of items < capacityof knapscak )

//Using bottom-Up Approach

// T = O(size * capacity)
// S = O(size * capacity)

#include<iostream>
#include<algorithm>

using namespace std;

int knapsack(int capacity, int weights[], int values[], int size)
{
    //dp[i][j] ---> Stores result for items {0...i-1} and capacity = j
    //Table construction to store results of sub-problems
    int **dp = new int*[size+1];
    for(int i = 0; i < size + 1; ++i)
      dp[i] = new int[capacity+1];

   for(int i = 0; i < size+1; ++i)
   {
       for(int w = 0; w < capacity+1; ++w)
       {
           //{ If total items = 0 --> (i=0)}  OR { weight = 0 ---> (w=0) }
           if(i == 0 || w == 0)
            dp[i][w] = 0;

           //Valid weight
           //Either include it OR exclude it
           else if(weights[i-1] <= w) 
              dp[i][w] = max(values[i-1] + dp[i-1][w-weights[i-1]],
                                           dp[i-1][w]); 
          else  // Invalid weight ---> Exclude it 
            dp[i][w] = dp[i-1][w];                                 
       }
   }
   return dp[size][capacity];
}

int main()
{
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int size = sizeof(weights)/sizeof(weights[0]);
    int capacity = 50;
    cout<<"\nMax Values(profits) possible : "<<knapsack(capacity, weights, values, size);
    return 0;
}