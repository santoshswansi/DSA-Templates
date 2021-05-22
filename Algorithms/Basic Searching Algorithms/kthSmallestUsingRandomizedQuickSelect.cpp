//Using Randomized QuickSelect to find the kth smallest element
// in an array of unsorted elements
//Given : All elements are distinct
//T = O(N^2) {Worst-Case}  T = O(N) {Average-Case}
//Use QuickSort
//If partitionIndex - 1  ==  k - 1 return the element
//Else recur in left or right sub-array A/T partitionIndex
//That is : If (partitionIndex -1 > k -1) --> recur left sub-array
//Else ----> recur right sub-array

#include <iostream>
#include <climits>

using namespace std;

void swap(int *no1, int *no2)
{
    int temp = *no1;
    *no1 = *no2;
    *no2 = temp;
}

//Standard partition function of quick sort
//Using  last element as pivot
int partition(int array[], int l, int r)
{
    int pivot = array[r];
    //put  the pivot in its exact position
    //(lesser-value element(s) are on left of pivot (Also same-value elem.))
    //(Higher-value element(s) are on right of pivot)
    int partitionIndex = l;
    for (int j = l; j <= r - 1; ++j)
    {
        if (array[j] <= pivot)
        {
            swap(&array[partitionIndex], &array[j]);
            ++partitionIndex;
        }
    }

    //swap rear element(pivot) with element at partitonIndex
    swap(&array[partitionIndex], &array[r]);

    return partitionIndex;
}

//Random partition
int randomPartition(int array[], int l, int r)
{
    int size = r-l+1;
    int randNum = rand()%size; 

    //Swap last element of array to element at randNum
    //So standard partition algorithm will bw called after
    //(pivot = last Elem)
    swap(&array[r], &array[l + randNum]);
    return partition(array, l, r);
}

//Find the k-th smallest element using quick sort algorithm
//Here k ---> position
//l & r -----> indices
int kthSmallest(int array[], int l, int r, int k)
{
    //Precautionary check for valid k

    if (k > 0 && k <= r - l + 1)
    {
        //Find the partitonIndex
        int partitionIndex = randomPartition(array, l, r);

        if (partitionIndex - l == k - 1)
            return array[partitionIndex];
        else if (partitionIndex - l > k - 1)
            return kthSmallest(array, l, partitionIndex - 1, k);
        return kthSmallest(array, partitionIndex + 1, r, k - (partitionIndex - l + 1));
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