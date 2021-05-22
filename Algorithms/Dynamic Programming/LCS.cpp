//Find the LONGEST COMMON SUBSEQUENCE of two strings 
//Tabulated Version of  DP
// T = O(size1 * size2)

#include<iostream>
#include<vector>

using namespace std;

int max(int no1, int no2)
{
    return (no1 > no2)? no1:no2;
}

int LCS(string str1, string str2, int size1, int size2)
{
  //To store solutions to  sub-problems  
  //LCS[i][j] ---> Stores longest common subsequence of string1[0---(i-1)]
  //               and string2[0---(j-1)] 
  vector<vector<int>> lcs(size1+1,vector<int> (size2+1, 0)) ;

  int i, j;
  for(i = 0; i <= size1; ++i)
  {
      for (j = 0; j <= size2; ++j)
      {
         if(i == 0 || j  == 0) //Any of the strings are empty
          lcs[i][j] = 0;  
         else if(str1[i-1] == str2[j-1] ) //If char matches
          lcs[i][j] = lcs[i-1][j-1] + 1;
         else    // char does not match
          lcs[i][j] = max(lcs[i-1][j], lcs[i][j-1]); 
      }
  }
  return lcs[size1][size2];
}
int main()
{
    string str1 = "AGGTAB";    // LCS = "GTAB" (length = 4)
    string str2 = "GXTXAYB";
    int size1 = str1.length();
    int size2 = str2.length();
    cout<<"\nLongest Common Subsequence : "<<LCS(str1, str2, size1, size2);
    return 0;
}