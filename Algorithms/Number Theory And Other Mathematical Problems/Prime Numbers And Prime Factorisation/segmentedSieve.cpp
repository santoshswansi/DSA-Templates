//Find all primes < given number using segmented sieve
//T = O(nlog(log(n)))
//S = 0(root(n))

#include<iostream>
#include<vector>
#include<math.h>

using namespace std;

//Find all primes < limit [Using simple sieve]
//Also stores primes in vector prime[]
void sieveOfEratosthenes(int num, vector<int> &prime)
{
    vector<bool> mark(num + 1, true);

    mark[0] = mark[1] = false;

    for (int i = 2; i * i <= num; ++i)
    {
        //Mark all multiples of prime as false
        if (mark[i])
        {
            for (int j = i * i; j <= num; j += i)
                mark[j] = false;
        }
    }

    //Print prime numbers (which are marked as true  in isPrime[] array)
    cout << "\nPrime numbers less than or equal to " << num << " are : \n";
    for (int i = 0; i < num; ++i)
    {
        if (mark[i])
        {
            prime.push_back(i);
            cout << i << " ";
        }
    }
}

//print all prime < number given
void segmentedSieve(int num)
{
    //Comput all primes <= root(num) [using simple sieve]
    int limit = floor(sqrt(num)) + 1;
    vector<int> prime;
    sieveOfEratosthenes(num, prime);

    //Divide range [0,n-1] in different segments
    int low = limit;
    int high = 2*limit;

    //While all segments are not processed, process each segment 
    //one by one
    while(low < num)
    {
       //Check for valid high
       if(high >= num)
         high = num;

       vector<bool> mark(limit+1, true);

       //Use found primes to find non-primes in given range
       for(int i = 0; i<prime.size(); ++i)
       {
           //Find minimum number in current range which is multiple of
           //prime[i]
           int lowLimit = floor(low/prime[i])*prime[i];

           for(int j = lowLimit; j < high; j+=prime[i])
             mark[j-low] = false;
       }
       

       //Print prime numbers
       for(int i = low; i <high; ++i)
         if(mark[i-low])
          cout<<i<<" ";

      //Update low and high values of next range
      low = low + limit;
      high = high + limit;    
    }
}

int main()
{
    int num = 50;
    segmentedSieve(50);
    return 0;
}