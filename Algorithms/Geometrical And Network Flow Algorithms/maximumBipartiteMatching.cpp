// Given a bipartite graph find the maximum matching
// MATCHING : A matching in a bipartite graph is a  set of edges
//            such that no two edges have same ending

// We can consider it a problem of assigning jobs to applicants such that 
// no applicant gets more than 1 job with maximum possible matching

#include<iostream>
#include<string.h>

using namespace std;
#define noOfApplicants 6
#define noOfJobs 6

//DFS based function 
//Returns true : If a job can be assigned to given applicant 
//Else false
bool bpm(bool bpGraph[noOfApplicants][noOfJobs], int appl, bool seen[],
         int matchAppl[noOfJobs])
{
  //Try all jobs one-by-one
  for(int job = 0; job < noOfJobs; ++job)
  {
      //applicant interested in job : 'job' and 'job' is not seen
      if(bpGraph[appl][job] == 1 && seen[job] == false)
      {
          //mark 'job' as seen
          seen[job] = true;

          // If job is not assigned
          //       OR
          // It is possible for previously assigned applicant 
          // to have other job available
          // SINCE we mark the current job seen the applicant will
          // not get the same job again
          if(matchAppl[job] < 0 || bpm(bpGraph, matchAppl[job], seen, matchAppl))
          {
              matchAppl[job] = appl;
              return true;
          }    
      }
  }
  return false;
}   

//Returns maximum matching from noOfApplicants to noOfJobs
int maxBPM(bool bpGraph[noOfApplicants][noOfJobs])
{
    int matchAppl[noOfJobs]; // stores applicants whose index= job
                             // -1(applicant not assigned)

    //All jobs are available 
    memset(matchAppl, -1, sizeof(matchAppl));     

    int result = 0;
    bool seen[noOfJobs];

    //Iterate for each applicants
    for(int i = 0; i<noOfApplicants; ++i)
    {
        //initialise seen for new applicant
        memset(seen, false, sizeof(seen));

        //Find if i-th applicant can  get a job or not
        if(bpm(bpGraph, i, seen, matchAppl))
          ++result;
    }   
    return result;                 
}

int main()
{

    // Let us create a bpGraph
    // bpGraph[i][j] : whether an i-th  applicant is interested in j-th job
    bool bpGraph[noOfApplicants][noOfJobs] = 
                         {{0, 1, 1, 0, 0, 0},
                          {1, 0, 0, 1, 0, 0},
                          {0, 0, 1, 0, 0, 0},
                          {0, 0, 1, 1, 0, 0},
                          {0, 0, 0, 0, 0, 0},
                          {0, 0, 0, 0, 0, 1}};

    cout << "Maximum number of applicants that can get job is "
         << maxBPM(bpGraph);

    return 0;
}