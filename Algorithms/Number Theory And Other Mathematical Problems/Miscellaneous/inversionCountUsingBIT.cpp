// Inversion count using Binary Indexed Tree (BI Tree) for +ve numbers

#include<iostream>
#include<vector>

using namespace std;

//Returns sum of array[0....index]
int getSum(vector<int> &BIT, int index)
{
    int sum = 0;
    while(index > 0)
    {
        sum += BIT[index];
        index -= index & (-index);
    }
    return sum;
}

//Returns sum of array[0....index]
void updateBIT(vector<int> &BIT, int n, int index, int val)
{
    while (index <= n)
    {
        BIT[index] += val;
        index += index & (-index);
    }
}

int inversionCount(vector<int> array)
{
    int size = array.size();
    int result = 0;

    //Find the maximum element
    int maxElement = array[0];
    for(int i = 1; i<size; ++i)
      if(array[i] > maxElement)
        maxElement = array[i];

    //Create a BI tree array of size = maxElement + 1  
    //( So that elements can directly be used as index) 
    vector<int> BIT(maxElement + 1);
    for(int i = 1; i <= maxElement; ++i)
       BIT[i] = 0;

    //Start from last to first
    for(int i = size-1; i>=0; --i)
    {
      //Get sum of elements smaller than array[i]  
      result += getSum(BIT, array[i] - 1);

      //Add current element to the BI Tree
      //Increase value by 1 where the current element is responsible for
      updateBIT(BIT, maxElement, array[i], 1); 
    }

    return result;
}

int main()
{
    vector<int> array = {20, 6, 5, 4, 1};

    cout << "\nInversion count = " << inversionCount(array);

    return 0;
}