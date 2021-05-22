// Inversion count using Binary Indexed Tree (BI Tree) (Supports -ve numbers)

#include <iostream>
#include <vector>
#include <set>
#include<algorithm>

using namespace std;

//Returns sum of array[0....index]
int getSum(vector<int> &BIT, int index)
{
    int sum = 0;
    while (index > 0)
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

//Convert the array with all positive numbers but relative order
//of elements should be maintained
void convert(vector<int> &array)
{
    int size = array.size();

    vector<int> temp = array;
    sort(temp.begin(), temp.end());

    //lower_bound() returns pointer to 1st element >= array[i]
    for(int i = 0; i < size; ++i)
       array[i] = lower_bound(temp.begin(), temp.end(), array[i]) -temp.begin() + 1;
   
}


int inversionCount(vector<int> array)
{
    int size = array.size();
    int result = 0;

    //Convert the array with all positive numbers but relative order
    //of elements should be maintained
    convert(array);

    //Find the maximum element
    int maxElement = array[0];
    for (int i = 1; i < size; ++i)
        if (array[i] > maxElement)
            maxElement = array[i];

    //Create a BI tree array of size = maxElement + 1
    //( So that elements can directly be used as index)
    vector<int> BIT(maxElement + 1);
    for (int i = 1; i <= maxElement; ++i)
        BIT[i] = 0;

    //Start from last to first
    for (int i = size - 1; i >= 0; --i)
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
    vector<int> array = {-1, -2, -3, -4, -5};

    cout << "\nInversion count = " << inversionCount(array);

    return 0;
}