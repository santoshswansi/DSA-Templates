// Given a square matrix where all numbers are distinct, find the maximum
// length path such that all cells along the path are in the increasing 
// order with a difference of 1.
// T = O(n^2)

#include<iostream>
#include<climits>
#include<algorithm>
#include<string.h>

using namespace std;
#define size 3

//To find the longest path from a cell
int findLongestPathFromACell(int rowIndex, int colIndex, int mat[size][size],
                                int dp[size][size])
{
   
   //Check for valid row and column index
   if(rowIndex < 0 || rowIndex > size-1 || colIndex < 0 || colIndex > size-1)
     return 0;

   //If sub-problem is already caculated
   if(dp[rowIndex][colIndex] != -1)
       return dp[rowIndex][colIndex];

   //To store path length in all 4 directions
   int up = INT_MIN, down = INT_MIN, left = INT_MIN, right = INT_MIN;

   //UP
   if(rowIndex > 0 && (mat[rowIndex][colIndex] + 1) == mat[rowIndex-1][colIndex])  
       up = 1 + findLongestPathFromACell(rowIndex-1, colIndex, mat, dp);

   //DOWN
   if (rowIndex < size-1 && (mat[rowIndex][colIndex] + 1) == mat[rowIndex + 1][colIndex])
       down = 1 + findLongestPathFromACell(rowIndex + 1, colIndex, mat, dp);
   
   //LEFT
   if (colIndex > 0 && (mat[rowIndex][colIndex] + 1) == mat[rowIndex][colIndex-1])
       left = 1 + findLongestPathFromACell(rowIndex, colIndex-1, mat, dp);
 
   //RIGHT
   if (colIndex < size-1 && (mat[rowIndex][colIndex] + 1) == mat[rowIndex][colIndex+1])
       right = 1 + findLongestPathFromACell(rowIndex, colIndex+1, mat, dp);

   return dp[rowIndex][colIndex] = max(up, max(down, max(left, max(right, 1))));     
}

//Overall longest path
int findLongestPathOverall(int mat[size][size])
{ 
   int longestPath = 1; // result

   int dp[size][size]; // for results  of sub-problems

   //Initialise dp with -1
   memset(dp, -1, sizeof(dp));

   for(int i = 0; i < size; ++i)
   {
       for(int j = 0; j < size; ++j)
       {
          if(dp[i][j] == -1)  // When sub-problem no calculated
            findLongestPathFromACell(i, j, mat, dp);
          longestPath = max(longestPath, dp[i][j]);  
       }
   } 
   return longestPath;  
} 

int main()
{
    int mat[size][size] = {
                           {1, 2, 9},          
                           {5, 3, 8}, 
                           {4, 6, 7}
                          };

    cout<<"\nLongest path in the given matrix : "<<findLongestPathOverall(mat);                      

    return 0;
}