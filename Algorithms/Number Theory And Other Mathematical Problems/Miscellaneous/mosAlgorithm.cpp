//Implementation of basic concepts of Mo's Algorithm

#include<iostream>
#include<algorithm>
#include<math.h>

using namespace std;

int blockSize;

struct Query
{
    int L, R;
};

//comparator function to sort queries
bool compare(Query query1, Query query2)
{
    //If both queries are not on the same block
    if(query1.L/blockSize != query2.L/blockSize) 
       return query1.L/blockSize < query2.L/blockSize;

    //If both queries are on the same block
    return query1.R < query2.R;
}

//m = total queries , n = total array elements
void queryResults(Query q[], int m, int array[], int n)
{
    blockSize = (int)sqrt(n);
    
    //Sort all queries
    sort(q, q+m, compare);

    int currL = 0, currR = 0;
    int currSum = 0;
    int L, R;

    //Traverse through all queries 
    for(int i = 0; i < m; ++i)
    {
       L = q[i].L;
       R = q[i].R;

       //Remove extra elements of previous range
       while(currL < L)
       {
          currSum -= array[currL];
          currL++;
       }

       //Add elements of current range
       while(currL > L)
       {
          currSum += array[currL-1];
          currL--;
       }

       while (currR <= R)
       {
          currSum += array[currR];
          currR++; 
       }  

       
       while(currR > R+1)
       {
          currSum -= array[currR-1];
          currR--;
       }
       cout<<"Sum("<<q[i].L<<", "<<q[i].R<<") = "<<currSum<<endl;
    }
}

int main()
{
    int array[] = {1, 2, 9,-1, 10, 7, 5, 11};
    int n = sizeof(array)/sizeof(array[0]);

    Query q[] = {{0,4},{2, 3},{4, 7},{1, 6},{5, 6},{3, 5}};
    int m = sizeof(q)/sizeof(q[0]);

    queryResults(q, m, array, n);
    return 0;
}