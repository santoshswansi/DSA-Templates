// Given set of equal number of men and women 
// Each people has a list of preferences in increasing order
// Marry them such that  there  are no two people of opposite sex 
// who would both rather have each other than their current partners

// If there are no such people, all the marriages are stable

#include<iostream>
#include<string.h>

using namespace std;
#define N  4// number of men or women

//Returns true if woman 'w' prefers man 'm1' over 'm'
// m1 - man with whom woman 'w' is currently engaged with
bool wPrefersM1OverM(int prefer[2*N][N], int w, int m, int m1)
{
    for(int i = 0; i < N; ++i)
    {
        // if 'm1' ocurrs before 'm' in preference list of 'w'
        if(prefer[w][i] == m1)
          return true;

        // if 'm' ocurrs before 'm1' in preference list of 'w'
        if (prefer[w][i] == m)
            return false;
    }
}

//Print stable matching from N boys to N girls
//Boys are indexed from 0 to (N-1)
//Girls are indexed from N to (2*N - 1)
void stableMarriage(int prefer[2*N][N])
{
    //wPartner[i] = partner assigned to women = N+i
    // -1 indicated partener not assigned 
    int wPartner[N];

    //Stores availability of men
    bool mFree[N];

    memset(wPartner, -1, sizeof(wPartner));
    memset(mFree, true, sizeof(mFree)); // all men are free

    int menFreeCount = N;

    //While there are free men
    while(menFreeCount > 0)
    {
        // pick the free man
        int m;
        for(m = 0; m < N; ++m)
          if(mFree[m])
           break;

        //One by one go to all women A/T m's preference
        // m = picked free man
        for(int i = 0; i < N && mFree[m] == true; ++i)
        {
            int w = prefer[m][i];
            if(wPartner[w-N] == -1) // women is free
            {
              wPartner[w-N] = m;
              mFree[m] = false;
              --menFreeCount;          
            }
            else // 'w' is not free
            {
              //get the assigned partner
              int m1 = wPartner[w-N];

              //If 'w' prefers m over m1(curr. engaged)
              //Break the engagement b/w 'w' and 'm1'
              //AND engage 'm' with 'w'
              if(wPrefersM1OverM(prefer, w, m, m1) == false)
              {
                  wPartner[w-N] = m;
                  mFree[m] = false; // occupied
                  mFree[m1] = true; // free
              }    
            } 
        }   
    }

    //Print the solution
    cout<<"WOMAN \t MAN"<<endl;
    for(int i = 0; i<N; ++i)
       cout<<" "<<i+N<<"\t"<<wPartner[i]<<endl;
}

int main()
{
    //Men -> Numbered from 0 -3
    //Women -> Numbered from 4-7
    int prefer[2 * N][N] = {
        {7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
    stableMarriage(prefer);
    return 0;
}