//Find the minimum distance(operation) that will require to convert
//one string to another  (Space Efficient Solution)

#include <iostream>
#include <vector>

using namespace std;

int min(int no1, int no2)
{
    return (no1 < no2) ? no1 : no2;
}

void editDistance(string str1, string str2)
{
    int size1 = str1.length();
    int size2 = str2.length();

    //dp[i][j] ---> Stores minimum operations to convert str1[0---(i-1)]
    //              to str2[0---(j-1)]
    vector<vector<int>> dp(2, vector<int>(size1 + 1, 0));

    for(int i = 0; i <= size1; ++i) //2nd string = empty ---> Remove all
        dp[0][i] = i;              //characters of 1st string

    for(int i = 1; i <= size2; ++i) //For each char of 2nd string
    {
        for(int j = 0; j <= size1; ++j) //For each char of 1st string
        {
           if(j == 0)  // 1st string = empty ---> Add all char of str2
             dp[i%2][j] = i; 
           else if(str1[j-1] == str2[i-1])
             dp[i%2][j] = dp[(i-1)%2][j-1];
           else
             dp[i%2][j] = 1 + min(min(dp[i%2][j-1],    //Insert
                                      dp[(i-1)%2][j]), //Remove     
                                  dp[(i-1)%2][j-1]);   //Replace 
        }     
    }

   //After filling dp[] : If size1 = even ---> row = 0
   //                     Else size2 = odd ---> row = 1
   cout<<dp[size2%2][size1]<<endl;
}

int main()
{
    string str1 = "sunday";
    string str2 = "saturday";
    cout << "\nMinimum edit distances(operations) to convert \"" << str1 << "\" to \""
         << str2 << "\" is ";
    editDistance(str1, str2);
    return 0;
}