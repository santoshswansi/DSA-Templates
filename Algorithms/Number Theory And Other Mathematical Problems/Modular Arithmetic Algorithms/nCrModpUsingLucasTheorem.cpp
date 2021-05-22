/* 
  Find nCr mod p using Lucas theorem | { when p is prime} |
                                     ______________________  
  T = O(p^2 * log(n) base p)
  Total digits in base-p representation of n is { log(n), base-p }
  Each digit < p 
  This implies computation of individual digit take O(p^2) time
*/

/*
   LUCAS THEOREM :
   We can find nCr % p by expressing n and r in base-p
     n = n0 * (p^0) + n1 * (p^1) + ....... + n(k-1) * (p^(k-1))
     r = r0 * (p^0) + r1 * (r^1) + ....... + r(k-1) * (p^(k-1))

   Now :
      nCr = (no)C(r0) * (n1)C(r1)*.......*( n(k-1) )C (r(k-1))   

*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int nCrModDP(int n, int r, int p)
{

    // We know nCr = nC(n-r)  if  r > (n-r)
    if (r > n - r)
        r = n - r;

    //C[] is going to store the last row elements of pascal's triangle
    vector<int> C(r + 1, 0);

    //C[0] = 1 (For any row)
    C[0] = 1;

    //Fill other rows
    // last element index of a row = row number
    for (int i = 1; i <= n; ++i)
    {
        // calculate upto r-indexed element of  row -i
        // Fill from right so that the previous calculated values
        // does not get  modified which are required
        for (int j = min(i, r); j > 0; --j)
            C[j] = (C[j] + C[j - 1]) % p;
    }
    return C[r];
}

//This function is like decimal to binary conversion
//First we compute last digits of n and r 
//and recur for  remaining digits
// P must be prime (ie. > 1)
int nCrModpLucas(int n, int r, int p)
{
    if(r == 0)
      return 1;  
 
    //Compute last digits of n and r in base-p
    int ni = n%p, ri = r%p;

    return (nCrModpLucas(n/p, r/p, p) * 
            nCrModDP(ni, ri, p))%p;   

}

int main()
{
    int n = 1000, r = 300, p = 13;
    cout<<"C("<<n<<", "<<r<<", "<<p<<" ) = "<<nCrModpLucas(n, r, p);
    return 0;
}