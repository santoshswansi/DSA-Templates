//Find all primes < given number using sieve of erotosthenes
//T = O(nlog(log(n)))

#include<iostream>
#include<vector>

using namespace std;

void sieveOfEratosthenes(int num)
{
    vector<bool> isPrime(num+1, true);

    isPrime[0]=isPrime[1] = false;

    for(int i = 2; i*i < num; ++i)
    {
        //Mark all multiples of prime as false
        if(isPrime[i])
        {
           for(int j = i*i; j <= num; j+=i)
              isPrime[j] = false;
        } 
    }

    //Print prime numbers (which are marked as true  in isPrime[] array)
    cout<<"\nPrime numbers less than or equal to "<<num<<" are : \n";
    for(int i = 0; i<num; ++i)
    {
        if(isPrime[i])
          cout<<i<<" ";
    }
}

int main()
{
    int num = 29;
    sieveOfEratosthenes(num);
    return 0;
}