//Linear time K-th smallest element in an unsorted array
// ALGORITHM : 
// 1---> Divide the elements into groups of 5 elements
// (last group may or may not have 5 elements )
// 2---> Find median of them and store it in median[] array
// 3---> Find median of median[]
// 4---> Find partitionIndex with pivot = median of median
// 5---> If ( partitionIndex == k) return (median of median)
// 6---> If ( partitionIndex > k)  recur left sub-array
// 7---> Else recur right sub-array 

// T = O(N)  {Worst-Case}

#include<iostream>
#include<climits>
#include<algorithm>

using namespace std;

void swap(int *no1, int *no2)
{
    int temp = *no1;
    *no1 = *no2;
    *no2 = temp;
}
//To find median 
int findMedian(int array[], int size)
{
    //Sort the elements of the array
    sort(array, array+size);
    return array[size/2];
}

int partition(int array[], int l , int r, int medOfMed)
{
  //Search pivot element
  int i;
  int partitionIndex = l;
  for(i=l; i <= r; ++i)
  {
      if(array[i] == medOfMed)
       break;
  }
  //Swap medOfMed with last element
  swap(&array[i], &array[r]);

  //Now Use standard partition algorithm
  for(i = l ; i <= r-1; ++i)
  {
    if(array[i] <= medOfMed)
    {
        swap(&array[i], &array[partitionIndex]);
        partitionIndex++;
    }
  }

  //Swap the last element with element at partitionIndex
  swap(&array[r], &array[partitionIndex]);
  return partitionIndex;
}

int kthSmallest(int array[], int l, int r, int k)
{
    if(k>0 && k <= r-l+1)
    {
      int size = r-l+1;

      //Form group of 5 elements
      //If size%5 == 0 ----> Total groups = size/5
      //Else if size%5 != 0 ----> Total groups = size/5 +1 {= (size+4)/5 }
      int *median = new int[(size+4)/5];  
      int i;

      for(i = 0 ; i < size/5; ++i) //For all groups(5 Elements)
       median[i] = findMedian(array + l + i*size, 5);
      
      if(i*5 < size) //For group(< 5 Elements)
       median[i] = findMedian(array + l + i*size, size%5);

      //Find Median of median using recursive calls
      //(i  == 1 --> only one group) : no recursive calls
      int medOfMed = (i == 1)? median[i-1] : kthSmallest(median, 0, i-1, i/2);

      //Find partitionIndex with pivot = medOfMed on median[] array
      int partitionIndex = partition(array, l, r, medOfMed);

      if(partitionIndex-l == k-1) 
         return array[partitionIndex];
      else if(partitionIndex-l > k-1)
         return kthSmallest(array, l, partitionIndex-1, k);
      return kthSmallest(array, partitionIndex+1, r, k-(partitionIndex-l+1));       
    }
    return INT_MAX;
}

int main()
{
    int array[] = {2, 9, 1, 8, 5, 10, 11, 24, 23, 16};
    int size = sizeof(array) / sizeof(array[0]);
    int k = 4;
    int result = kthSmallest(array, 0, size - 1, k);
    if (result != INT_MAX)
        cout << "\n4th smallest element is : " << result;
    else
        cout << "\nInvalid index";
    return 0;
}