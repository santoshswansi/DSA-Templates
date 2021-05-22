//Manachar's Algorithm - To find Longest palindromic substring in the given
// text

#include<iostream>
#include<algorithm>
#include<string.h>

using namespace std;

string getModifiedString(string text)
{
    string modifiedString = "";
    int textSize = text.length();
    for(int i = 0; i < textSize; ++i)
    {
        //substr(l,r) --> r-exclusive
        modifiedString += "#" + text.substr(i,1);  
    }
    modifiedString += "#";
    return modifiedString;
}

int manacharAlgorithm(string text)
{
 
  //First modify the string 
  text = getModifiedString(text);

  int length = text.length();
 
  int *LPS = new int[length]; //Contains all palindromic substring
  
  //Initialise LPS with 0              // sizeof(int)*length : CORRECT 
  memset(LPS, 0, sizeof(int)*length);  // sizeof(LPS) : WRONG

  //Variables for current LPS
  int center = 0, right = 0;
  int maxLen = 0;

  for(int i = 0; i < length; ++i)
  {
      int mirror = 2*center - i; //Get the mirror of index 'i'

      //See if the mirror of 'i' is expanding beyond the left boundary
      //of current LPS at centered at 'center'
      //If it is, then take { 'rear' - i } as LPS[i]
      //Else, take LPS[mirror] as LPS[i]
      if(i < right)
      {
        LPS[i] = min(right-i, LPS[mirror]);
      } 

      //Expand at 'i'
      int leftCharIndex = i - (LPS[i] + 1);
      int rightCharIndex = i + (LPS[i] + 1);

      while(leftCharIndex >= 0 && rightCharIndex < length &&
                 text[leftCharIndex] == text[rightCharIndex])
      {
          ++LPS[i];
          --leftCharIndex;
          ++rightCharIndex;
      }     

      //Check if the expanded palindrome centered at 'i' is exapnding
      //beyond right boundary of current LPS centered at 'center'
      //If it is : New center is 'i'
      if(i + LPS[i] > right)
      {
          center = i;
          right = i + LPS[i];

          //Update the max length LPS
          if(LPS[i] > maxLen)
          {
              maxLen = LPS[i];
          }
      }
  }
  return maxLen;
}

int main()
{           //          _______    :  LPS
    string text = "abcbagjfgfjgysj";
    int maxLenLPS = manacharAlgorithm(text);
    cout<<"\nMax Length LPS is "<<maxLenLPS;

    return 0;
}