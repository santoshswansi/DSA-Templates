// KMP Algorithm to find pattern(pat) in a text(txt) 
// T = O(N)
// ALGORITHM
// 1-> Create a LPS[] array { Longest proper prefix which is also suffix}
// 2-> Use LPS to skip the certain number of character which will match
//     anyway after finding a mismatch after a number of matches

#include<iostream>
#include<string.h>

int computeLPS(char *pattern , int patLength, int *LPS)
{
    LPS[0] = 0; //initialise LPS[0] = 0
    int i = 1;
    int currLPSLength = 0;
    while(i < patLength)
    {
        if(pattern[i] == pattern[currLPSLength])
        {
            ++currLPSLength;
            LPS[i] = currLPSLength;
            ++i;
        }
        else //Mismatch
        {
            //Mismatch after a non-zero number of matches
            //Update the currLPSLength = LPS[currLPSLength-1]
            if(currLPSLength != 0)
              currLPSLength = LPS[currLPSLength-1]; //Don't increase 'i'
            else
            {
               LPS[i] = 0;
               ++i;   
            }  
        }
        
    }
}

void  KMPSearch(char *text, char *pattern)
{
    int patLength = strlen(pattern);
    int textLength = strlen(text);

    int *LPS = new int[patLength];

    computeLPS(pattern, patLength, LPS);

    int i = 0; //index of text[]
    int j = 0; //index of pattern[]

    while (i < textLength)
    {
       //If there is a match increase indexes of pattern and text
       if(text[i] == pattern[j])
         ++i, ++j;

       //Check if j == patLength (Print pattern found at index i-patLength)
       if(j == patLength)  
       {
           printf("\nPattern found at index :  %d", i - j); //(i-patLength)
           j = LPS[j-1];
       }
       //Mismatch after j matches
       else if(i < textLength && pattern[j] != text[i])
       {
          //Skip LPS[j-1] characters of pattern
          if(j != 0)
            j = LPS[j-1];
          else        //If first character does not match
            i += 1;   
       }
    }
}

int main()
{
   char text[] = "ABABDASEAVAEDAWEVABAAABAFV";
   char pattern[] = "AB";  
   KMPSearch(text, pattern);
   return 0;
}