//Searching pattern in a text using standard sorting 
//algorithm which takes O(NLogN) 

#include<iostream>
#include<string.h>
#include<algorithm>

using namespace  std;

//Data structure to store suffix of a text
struct Suffix
{
 int index; //To store original index
 int rank[2];//To  store rank and next rank pair
};

//comparator function
int compare(Suffix suff1,Suffix suff2)
{
  return (suff1.rank[0]==suff2.rank[0])?(suff1.rank[1]<suff2.rank[1]?1:0):
         (suff1.rank[0]<suff2.rank[0]?1:0); 
}

int* buildSuffixArray(char *text,int size)
{
  Suffix *suffixes=new Suffix[size];
  for(int i=0;i<size;++i)
  {
    suffixes[i].index=i;
    suffixes[i].rank[0]= text[i]-'a';  
    suffixes[i].rank[1]=((i+1)<size)?(text[i+1]-'a'):-1;
  }  

  sort(suffixes,suffixes+size,compare);
  
  //All suffixes are sorted A/T first 2 characters
  //Let us now sort suffixes A/T first 4,first 8, ..., 2*size characters

  //an array to get the index in suffixes[] from original index
  //It is used for getting the next suffix
  int *index;

  for(int k=4;k<2*size;k*=2) 
  {
    //Assigning index and first rank to first suffix  
    int rank=0;  
    int prevRank=suffixes[0].rank[0];//store the rank of the 1st suffix
    suffixes[0].rank[0]=rank; 
    index[suffixes[0].index]=0;

    //Assign first rank to other suffixes
    for(int i=1; i<size;++i)
    {
      //If rank and next rank of previous suffix and this suffix is same 
      //Assign same rank
      if(suffixes[i].rank[0]==prevRank
        && suffixes[i].rank[1]==suffixes[i-1].rank[1])
      {
        prevRank=suffixes[i].rank[0];  
        suffixes[i].rank[0] = rank;
      } 
      else
      {
        prevRank=suffixes[i].rank[0];
        suffixes[i].rank[0]=++rank;
      }
      index[suffixes[i].index]=i;
    }

    //Assign next rank to every suffix
    for(int i=0;i<size;++i)
    {
      int nextIndex = suffixes[i].index + k/2;
      suffixes[i].rank[1]=(nextIndex<size)?
                          (suffixes[index[nextIndex]].rank[0]):-1;  
    }
    sort(suffixes,suffixes+size,compare);
  }

  //Assign values to the suffix array
  int *suffixArray=new int[size];
  for(int i=0;i<size;++i)
    suffixArray[i]=suffixes[i].index;
  return suffixArray;  
}

//Since we have sorted array of all suffixes of the text
void search(char *text, char *pattern, int *suffixArray, int sizeText)
{
    int sizePattern = strlen(pattern); //get the length of the pattern
    int start = 0;
    int end = sizeText - 1;
    int middle;
    while (start <= end)
    {
        middle = start + (end - start) / 2;
        //compare the 'sizePattern' characters starting from suffixArray[middle]
        int result = strncmp(pattern, text + suffixArray[middle], sizePattern);

        if (result == 0)
        {
            cout << "\nPattern is found at index : " << suffixArray[middle];
            return;
        }
           
        if (result < 0)
            end = middle - 1;
        else
            start = middle + 1;
    }
    cout << "\nPattern not found!";
}

void printArray(int array[],int size)
{
  for(int i=0;i<size;++i)
   cout<<array[i]<<" ";
  cout<<endl;    
}

int main()
{
    char text[] = "banana";
    char pattern[] = "nan";
    int size = strlen(text);

    int *suffixArray = buildSuffixArray(text, size);

    cout<<"\nSuffix Array for text "<<text<<" is : "<<endl;
    printArray(suffixArray,size);
    search(text, pattern, suffixArray, size);
    return 0;
}