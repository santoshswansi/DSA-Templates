// Given an array of elements . You have to select elements such that 
// you end up getting maximum sum
// CONSTRAINTS : 1.)  You can pick the elements at the two-ends only
//               2.)  Each player get alternating chance to choose

#include<iostream>
#include<algorithm>

using namespace std;

int optimalStrategyOfAGame(int array[], int size)
{
    //table to store sub-problems
    // dp[i][j] --> stores the result for array[i----j]
    int **dp = new int*[size];  //Rows

    //Allocate memory for columns
    for(int i = 0; i < size; ++i)
      dp[i]  = new int[size];

    // Table will be filled in diagonal fashion 
    // From diagonal elements to table[0][size-1] (result)
    // { i ----> start index } AND { j ----> end index }
    for(int gap = 0; gap < size; ++gap)
    {
        for(int i = 0, j = gap; j < size; ++i, ++j)
        {
            // F(i,j) : max value the user can collect from i-th item
            // to j-th item

            // x = value of F(i+2, j)
            // y = value of F(i+1, j-1)
            // z = value of F(i, j-2)

            int x = ((i+2) <= j)? dp[i+2][j] : 0;
            int y = ((i+1) <= (j-1))? dp[i+1][j-1] : 0;
            int z = (i <= (j-2))? dp[i][j-2] : 0;
 
            // { array[i] + min(x, y) }
            // select i-th element and minimum of 2-largest elements
            // out of 4 elements at the edges( 2 on both sides )
            dp[i][j] = max((array[i] + min(x,y)), (array[j] + min(y,z)));
        }
    }  
    return dp[0][size-1];
}
int main()
{
    int array1[] = {5, 3, 7, 10};
    int size = sizeof(array1)/sizeof(array1[0]);
    cout<<"\n RESULT - 1:"<<optimalStrategyOfAGame(array1, size);

    int array2[] = {8, 15, 3, 7};
    size = sizeof(array2)/sizeof(array2[0]);
    cout << "\n RESULT - 2:" << optimalStrategyOfAGame(array2, size);

    return 0;
}