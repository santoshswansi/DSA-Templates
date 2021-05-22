//Given a distance, count total number of ways to cover the distance 
//with 1, 2 and 3 steps
// T =  O(n)

#include<iostream>

using namespace std;

int printCount(int dist)
{
    // count[i] ---> total ways to cover distance 'i'
    int *count = new int[dist+1];
    count[0] = 1, count[1] = 1, count[2] = 2;
    for(int i = 3; i <= dist; ++i)
    {
        count[i] = count[i-1] + count[i-2] + count[i-3];
    }
    return count[dist];
}
int main()
{
    int dist = 3; // distance to cover
    cout<<"\nDistance of "<<dist<<" can be covered in "<<
          " (using steps 1, 2 and 3) : "<<printCount(dist);
        
    return 0;
}