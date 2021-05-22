// Given an array of items with their weights and values(profits)
// and a knapsack of fixed capacity
// We need to put items in the knapsack so that sum of their values
// would be maximum (weight of items < capacityof knapscak )

//Using Memoized Technique

// T = O(size * capacity)
// S = O(size * capacity)

#include <iostream>
#include <algorithm>
#include <string.h>

using namespace std;

int knapsackUtil(int remCapacity, int weights[], int values[], int remIndex, int **dp)
{

   if(remIndex < 0) 
    return 0; 

   //If result of sub-problem already calculated
   if(dp[remIndex][remCapacity] != -1)
       return dp[remIndex][remCapacity];

   //If the weight of element > remaining capacity
   //Ignore the element
   if(weights[remIndex] > remCapacity)
   {
      dp[remIndex][remCapacity] = knapsackUtil(remCapacity, weights, values, remIndex-1, dp);
      return dp[remIndex][remCapacity];
   }

   // Else if it is valid weight 
   // Either include it OR exclude it
   // Return max of it
   else
   {
     dp[remIndex][remCapacity] =
       max(values[remIndex] +
       knapsackUtil(remCapacity - weights[remIndex], weights, values, remIndex - 1, dp),
       knapsackUtil(remCapacity, weights, values, remIndex - 1, dp));
     
     // return value of table after storing
     return dp[remIndex][remCapacity];  
   } 

}

//wrapper function of knapsackUtil
int knapsack(int weights[], int values[], int size, int capacity)
{
   // create table dynamically 
   int **dp = new int*[size];
   for(int i = 0; i < size; ++i)
      dp[i] = new int[capacity + 1];

  //Initialise dp with -1
  for(int i = 0; i < size; ++i)
      for(int j = 0; j < capacity+1; ++j)
           dp[i][j] = -1;

  return knapsackUtil(capacity, weights, values, size-1, dp);  
}

int main()
{
    int values[] = {60, 100, 120};
    int weights[] = {10, 20, 30};
    int size = sizeof(weights) / sizeof(weights[0]);
    int capacity = 50;
    cout << "\nMax Values(profits) possible : " << knapsack(weights, values, size, capacity);
    return 0;
}