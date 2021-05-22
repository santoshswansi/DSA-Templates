// Sieve of Eratosthenes in O(n) time complexity
#include<iostream>
#include<vector>

using namespace std;

void sieveOfEratosthenesInLinearTime(int num)
{
    vector<bool> isPrime(num, true);
    vector<int> prime;
    vector<int> SPF(num); // Stores smallest prime factor of number

    int sizeOfPrime = 0;

    // 0 and 1 are not prime
    isPrime[0] = isPrime[1] = false;
    int k =0;

    for(int i = 2; i <= num; ++i) 
    {
       if(isPrime[i])
       {
           prime.push_back(i);
           SPF[i] = i; //Smallest common factor of prime is itself
       }

       //Remove all multiples of i*prime[j] which are not 
       //prime by making isPrime[i*prime[i]] to false
       //             AND
       //Make SPF[i*prime[j]] = prime[j]
       //Runs only one time for composite number  
       for(int j = 0; j < prime.size() &&
                          i*prime[j] < num &&
                          prime[j] <= SPF[i];  ++j)
       {
           isPrime[i*prime[j]] = false;
           SPF[i*prime[j]] = prime[j];
       }                   
    }
   
    cout << "\nPrime numbers less than or equal to " << num << " are : \n";
    for (int i = 0; i < prime.size() && prime[i] <= num; ++i)
    {
            cout << prime[i] << " ";
    }
}

int main()
{
    int num = 50;
    sieveOfEratosthenesInLinearTime(num);
    return 0;
}