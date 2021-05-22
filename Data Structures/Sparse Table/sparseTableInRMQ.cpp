#include<iostream>
#include<math.h>

using namespace std;
#define MAX 500

int lookup[MAX][MAX]; //sparse table OR sparse matrix

struct Query
{
 int L,R;
};

void preprocess(int array[],int arrSize)
{
 //Initialise intervals with length 1
 for(int i=0;i<arrSize;++i)
  lookup[i][0]=i;

 //compute values from smaller to bigger values
 for(int j=1; (1<<j) <= arrSize; ++j)
 {
  //compute minimum values for all intervals with size 2^j
  for(int i=0; (i+(1<<j)-1) < arrSize; ++i)
  {
   if(array[lookup[i][j-1]] <= array[lookup[i + (1 << (j-1))][j-1]])
    lookup[i][j] = lookup[i][j-1];
   else
       lookup[i][j] = lookup[i + (1 << (j - 1))][j - 1];
  } 
 } 
}

//returns minimum of array[L...R]
int query(int array[], int L, int R)
{
  int j = (int)log2(R-L+1); //closest power of 2 
  if(array[lookup[L][j]] <= array[lookup[R - (1<<j) + 1][j]])
   return array[lookup[L][j]];
  else
   return array[lookup[R - (1 << j) + 1][j]];
}

void RMQ(int array[], int arrSize, Query q[], int totQuery)
{
  preprocess(array, arrSize);
  for(int i=0; i<totQuery; ++i)
  {
   int L=q[i].L;
   int R=q[i].R;
   cout<<"\nMinimum of ["<<L<<","<<R<<"] is "<<query(array,L,R);   
  }
}
int main()
{
  int array[] = {1,2,-1,7,9,12,10,8,13,18};
  int arrSize = sizeof(array)/sizeof(array[0]);
  Query q[] = {{0,5},{0,1},{7,9},{2,9}};
  int totQuery=sizeof(q)/sizeof(q[0]);
  RMQ(array, arrSize, q, totQuery);
  return 0;  
}