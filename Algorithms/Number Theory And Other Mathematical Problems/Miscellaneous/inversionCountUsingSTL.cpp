// Inversion Count using STL
// T = O(n^2)

#include<iostream>
#include<set>
#include<vector>

using namespace std;

int inversionCount(vector<int> array)
{
    int size = array.size();
    multiset<int> set1;
    int result = 0;

    set1.insert(array[0]);

    multiset<int>::iterator it;

    for(int i = 1; i < size; ++i)
    {
       //Insert element into  the multiset 
       set1.insert(array[i]);

       //Find the iterator to first element > array[i]
       it = set1.upper_bound(array[i]);

       result += distance(it, set1.end());
    }
    return result;
}

int main()
{
    vector<int> array = {-1, -2, -3, -4, -5};

    cout << "\nInversion count = " << inversionCount(array);

    return 0;
}