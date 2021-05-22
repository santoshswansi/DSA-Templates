// nCr can be found by looking at element (r+1) in row = n
// T = O(n*r)
// s = O(r)

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int nCrModp(int n, int r, int p)
{
    // We know nCr = nC(n-r)  if  r > (n-r)
    if(r > n-r)
      r = n-r;

    //C[] is going to store the last row elements of pascal's triangle
    vector<int> C(r+1, 0);  

    //C[0] = 1 (For any row)
    C[0] = 1;

    //Fill other rows
    // last element index of a row = row number
    for(int i = 1; i<=n; ++i)  
    {
        // calculate upto r-indexed element of  row -i
        // Fill from right so that the previous calculated values 
        // does not get  modified which are required
        for(int j = min(i, r); j > 0; --j)
          C[j] = (C[j] + C[j-1])%p;
          
    }
    return C[r];
}

int main()
{
    int n = 1000, r = 300, p = 13; 
    cout<<"C("<<n<<", "<<r<<", "<<p<<" ) = "<<nCrModp(n, r, p);
    return 0;
}