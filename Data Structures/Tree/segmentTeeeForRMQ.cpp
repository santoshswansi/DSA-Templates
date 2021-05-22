#include <iostream>
#include <math.h>
#include<limits.h>

using namespace std;

//si is the index of current node in the segment tree
//ss & se are the starting and ending indices of segment segmentTree[si]
//qs and qe are the starting and ending indices of query

int getMid(int start, int end)
{
    return (start + (end - start) / 2);
}

int minValue(int no1,int no2)
{
  return (no1<no2) ? no1 : no2;  
}

int RMQUtil(int *segmentTree, int ss,int se, int qs, int qe, int si)
{
  if(qs<=ss && qe>=se)
   return segmentTree[si];
  if(qs>se || qe<ss)
   return INT_MAX; 
  int mid=getMid(ss,se);
  return minValue(RMQUtil(segmentTree,ss,mid,qs,qe,si*2+1),
                RMQUtil(segmentTree,mid+1,se,qs,qe,si*2+2));
}

int RMQ(int *segmentTree,int size,int qs,int qe)
{
  if(qs<0 || qe>size-1 || qs>qe)
  {
    cout<<"\nInvalid Input!";
    return -1;  
  }
  return RMQUtil(segmentTree,0,size-1,qs,qe,0);
}

int constructSegmentTreeUtil(int array[], int ss, int se, int *segmentTree, int si)
{
    if (ss == se) //Only one element in array
    {
        segmentTree[si] = array[ss];
        return array[ss];
    }
    int mid = getMid(ss, se);
    segmentTree[si] = minValue(constructSegmentTreeUtil(array, ss, mid, segmentTree, 2 * si + 1),
                    constructSegmentTreeUtil(array, mid + 1, se, segmentTree, 2 * si + 2));
    return segmentTree[si];
}

int* constructSegmentTree(int array[], int size)
{
    int x = (int)(ceil(log2(size)));
    int maxSize = 2 * (int)pow(2, x) - 1; //maximum size of segment tree
    int *segmentTree = new int[maxSize];
    constructSegmentTreeUtil(array, 0, size - 1, segmentTree, 0);
    return segmentTree;
}

int main()
{
    int array[] = {1, 5, 2, 6, 8, 7};
    int size = sizeof(array) / sizeof(array[0]);
    int *segmentTree = constructSegmentTree(array, size);

    cout<<"\nMin value in [0-2] : "<<RMQ(segmentTree,size,0,2);
    cout<<"\nMin value in [1-5] : "<<RMQ(segmentTree, size, 1, 5);
    cout << "\nMin value in [3-5] : " << RMQ(segmentTree, size, 3, 5);
    return 0;
}