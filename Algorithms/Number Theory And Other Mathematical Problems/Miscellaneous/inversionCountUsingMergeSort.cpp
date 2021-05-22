// Inversion count of an array using merge sort
// T = O(nlog(n))

#include<iostream>
#include<vector>

using namespace std;

// Merge sort based function to get inversion count of an array
void mergeSort(vector<int> &array, vector<int> &temp, int left, int right, int &result);

//Merge two sorted arrays
void merge(vector<int> &array, vector<int> &temp, int left, int mid, int right, int &result);

// To get inversion count using merge sort
int inversionCount(vector<int> array)
{
    int size =  array.size();
    vector<int> temp(size);
    int result = 0;
    mergeSort(array, temp, 0, size-1,result);
    
    return result;
}

// Merge sort based function to get inversion count of an array
void mergeSort(vector<int> &array, vector<int> &temp, int left, int right, int &result)
{
   if(left < right)
   {
       //Divide the array
       int mid = (left + right)/2;
       mergeSort(array, temp, left, mid, result);
       mergeSort(array, temp, mid+1, right, result);

       merge(array, temp, left, mid, right, result); 
   }
}

//Merge two sorted arrays
void merge(vector<int> &array, vector<int> &temp, int left, int mid, int right, int &result)
{
    int i = left; //index for left array
    int j = mid + 1; // index for right array
    int k = left; // index for merged array

    while(i<= mid && j<=right)
    {
        if(array[i] <= array[j])
        {
            temp[k++] = array[i++];
        }
        else // array[i] > array[j] ---> Update result
        {
            temp[k++] = array[j++];
            result += (mid + 1) - i;  
        }
    }

    //Left out elements in any of the  sub-arrays
    while(i <= mid)
    {
      temp[k++] = array[i++];
    }

    while(j <= right)
    {
      temp[k++] = array[j++]; 
    }

    //Update the original sub-array with the sorted sub-array
    for(int i = left; i <= right; ++i)
      array[i] = temp[i];
}

int main()
{
  vector<int> array = {20, 6, 5, 4, 1};
  cout<<"\nInversion count = "<<inversionCount(array);
  return 0;
}