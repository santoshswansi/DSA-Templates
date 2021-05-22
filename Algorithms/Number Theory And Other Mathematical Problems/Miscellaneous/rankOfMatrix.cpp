/*
: Rank of a matrix
: Since it involve floating-point value, it may produce incorrect result
   if the division goes beyond precision.
: T = O(n^3)
*/

#include<iostream>

using namespace std;

#define R 3
#define C 3

//To swap to rows
void swap(int mat[R][C], int row1, int row2, int col)
{
    for(int i = 0; i < col; ++i)
    {
        int temp = mat[row1][i];
        mat[row1][i] = mat[row2][i];
        mat[row2][i] = temp;
    }
}

void display(int mat[R][C], int row, int col)
{
    for(int i = 0; i<row; ++i)
    {
        for(int j = 0; j<col; ++j)
          cout<<mat[i][j]<<" ";
        cout<<endl;  
    }
}

int matrixRank(int mat[R][C])
{
   //Initialise rank with number of columns
   int rank = C;

   for(int col = 0; col < rank; ++col)
   {
       //Diagonal element != 0 make all other elements in the column 0
       if(mat[col][col] != 0)
       {
          for(int row = 0; row < R; ++row)
          {
              if(row != col)
              {
                  double mult = (double)mat[row][col]/mat[col][col];

                  for(int i = 0; i<rank; ++i)
                    mat[row][i] -= mult*mat[col][i];
              }
          } 
       }
       else //Diagonal element = 0
       {
          // Find the non-zero element below it in the same column

          bool reduceRank = true;

          for(int i = col+1; i < R; ++i)
          {
             if(mat[i][col] != 0) // non-zero element found
             {
                //Swap the rows
                swap(mat, col, i, rank);
                reduceRank = false;
                break;
             } 
          }  

          //If we have not find non-zero element below it
          if(reduceRank)
          {
              //Reduce rank;
              rank--;

              //Copy the last column elements here
              for(int i = 0; i < R; ++i)
               mat[i][col] = mat[i][rank];
          } 
          col--; //process this row again with new set of values
       }
   }
   return rank;
}

int main()
{
    int mat[R][C] = {{10, 20, 10},
                     {-20, -30, 10},
                     {30, 50, 0}};
    cout<<"Matrix Rank = "<<matrixRank(mat); 

    cout<<"\nProcessed Matrix : \n";
    display(mat, R, C);

    return 0;
}