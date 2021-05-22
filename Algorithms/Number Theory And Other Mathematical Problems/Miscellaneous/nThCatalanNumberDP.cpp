//DP Solution to find nth catalan number
#include<iostream>
#include<vector>

using namespace std;

int nthCatalanNumber(int number)
{
    vector<unsigned int> catalan(number+1);

    catalan[0] = catalan[1] = 1;

    for(int i = 2; i <= number; ++i)
    {
        catalan[i] = 0;
        for(int j = 0 ; j < i; ++j)
        {
            catalan[i] += catalan[j]*catalan[i-j-1];
        }
    }
    return catalan[number];
}

int main()
{
    int number = 7;
    cout<<number<<"th Catalan Number = "<<nthCatalanNumber(number);
    return 0;
}