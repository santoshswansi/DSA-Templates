//Rabin Karp algorithm for pattern searching
// T = O(patLength + textLength) {Average-Case}
// T = O(patLength * textLength) {Worst-Case}

#include<iostream>
#include<string.h>

using namespace std;

#define totalChar 256 // number of characters

int rabinKarpSearch(char text[], char pattern[], int primeNo)
{
  int patLength  = strlen(pattern);
  int textLength = strlen(text);

  int i, j;
  int hValuePattern = 0; //hash value of pattern
  int hValueText = 0; // hash value of text

  //Most significant digit multiplier
  int MSDMultiplier = 1; //pow(totalChar, patLength-1) 

  //calculate MSDMultiplier
  //(In such a way that it does not get out of range of int)
  for(i = 0; i < patLength-1; ++i)
   MSDMultiplier = (MSDMultiplier * totalChar) % primeNo;
  
  //Calculate the  hash values of pattern and first window of text
  for(i = 0; i < patLength; ++i)
  {
      hValuePattern = (totalChar*hValuePattern + pattern[i])%primeNo;
      hValueText = (totalChar*hValueText + text[i])%primeNo;
  } 

  for(i = 0; i < textLength-patLength; ++i)
  {
      if(hValueText ==  hValuePattern)
      {
          //Check one-by-one
          for(j = 0; j < patLength; ++j)
          {
              if(text[i+j] != pattern[j])
                break;
          }
        
          if(j == patLength)
           cout<<"\nPattern found at index : "<<i;
      }
      if(i < textLength - patLength)
      {
          //Calculate hash  value of next window of text
          hValueText = (totalChar*(hValueText - MSDMultiplier*text[i])
                           + text[i+patLength])%primeNo;
          if(hValueText < 0 ) //handle negative hash value
           hValueText += primeNo;                 
      }
  }
}

int main()
{
    char text[] = "ABABDASEAVAEDAWEVABAAABAFV";
    char pattern[] = "AB";
    int primeNo = 101; // A prime number
    rabinKarpSearch(text, pattern, primeNo);
    return 0;
}