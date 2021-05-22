//Find the minimum distance(operation) that will require to convert
//one string to another

#include<iostream>
#include<vector>

using namespace std;

int min(int no1, int no2)
{
    return (no1 < no2)?no1:no2;
}

int editDistance(string str1, string str2)
{
    int size1 = str1.length();
    int size2 = str2.length();
    
    //dp[i][j] ---> Stores minimum operations to convert str1[0---(i-1)]
    //              to str2[0---(j-1)]
    vector<vector<int>> dp(size1+1, vector<int> (size2+1, 0));

    for(int i = 0 ; i<=size1; ++i)
    {
        for(int j = 0; j <=size2; ++j)
        {
            if(i==0) // str1 = empty --> Add all characters of 'str2'
             dp[i][j] = j;
            else if(j==0) //str2 = empty --> Remove all characters of 'str1'  
             dp[i][j] = i;  
            else if(str1[i-1] == str2[j-1]) // Last char matched 
             dp[i][j] = dp[i-1][j-1];
            else //Last char did not matched (Minimum of three operations)
             dp[i][j] = 1 + min( min(dp[i][j-1],   // Insert  (left)
                                     dp[i-1][j]),  // Remove  (up)
                                 dp[i-1][j-1]      // Replace (diagonal)
                               );
        }
    }
    return dp[size1][size2];  
}
int main()
{
    string str1 = "sunday";
    string str2 = "saturday";
    cout<<"\nMinimum edit distances(operations) to convert \""<<str1<<"\" to \""
        <<str2<<"\" is "<<editDistance(str1, str2);
    return 0;
}