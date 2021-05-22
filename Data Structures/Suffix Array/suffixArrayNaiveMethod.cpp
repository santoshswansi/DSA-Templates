//Search a pattern using Suffix Array(Naive Approach)
//Time Complexity : O(n^2Logn)

#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

//Data structure to hold a suffix of the text
struct Suffix
{
 int index;
 char *suff; 
};

//Comparator function
//If returns true exchange them, otherwise : DO NOTHING
int compare(Suffix suff1, Suffix suff2)
{
  return strcmp(suff1.suff,suff2.suff)<0?1:0;   
}

int* buildSuffixArray(char *text, int size)
{
  Suffix *suffixes=new Suffix[size]; //to store size suffixes of the text
  
  //Fill 'suffixes' vector with all possible suffixes of 'text'
  //along with its starting index

  for(int i=0;i<size;++i)
  {
    suffixes[i].index=i;
    suffixes[i].suff=(text+i);  
  }
  
  //sorting vector suffixes using comparator function
  sort(suffixes, suffixes+size, compare);

  //After sorting store the original index of suffixes in a suffixArray
  int *suffixArray=new int[size];
  for(int i=0; i<size ; ++i)
    suffixArray[i]=suffixes[i].index;

  return suffixArray; 
}

//Since we have sorted array of all suffixes of the text
void search(char *text, char *pattern,int *suffixArray,int sizeText)
{
  int sizePattern=strlen(pattern); //get the length of the pattern
  int start=0;
  int end=sizeText-1;
  int middle;
  while (start<=end)
  {
    middle=start + (end-start)/2;
    //compare the 'sizePattern' characters starting from suffixArray[middle]
    int result=strncmp(pattern, text+suffixArray[middle], sizePattern);

    if(result==0)
    {
      cout << "\nPattern is found at index : " << suffixArray[middle];
      return;
    }
    
    if(result<0)
     end=middle-1;
    else
     start=middle+1; 
  }
  cout<<"\nPattern not found!";
}

void printArray(int array[], int size)
{
  for (int i = 0; i < size; ++i)
    cout << array[i] << " ";
  cout << endl;
}

int main()
{
  char text[]="madam maya";
  char pattern[]="ya";
  int size=strlen(text);

  int *suffixArray=buildSuffixArray(text,size);

  cout << "\nSuffix Array for text : " << text << " is : " << endl;
  printArray(suffixArray, size);
  search(text, pattern, suffixArray, size);
  return 0;  
}