#include<iostream>
#include<vector>

using namespace std;
#define NO_Of_CHARS 256

int getNextState(string pattern,int patternSize,int state,int ch)
{
  //if current character x is same as next character  
  //Simply increment the state
  //Total states :  (patternSize+1)
  //"state" range : (0-patternSize)
  if(state< patternSize && ch == pattern[state])
   return state+1;

  //nextState stores the result 
  int nextState, i;

  //nextState will finally contain the longest prefix
  //which is also suffix in "pattern[0...state-1]ch"

  //Start from the longest possible value and stop when you 
  //find a prefix which is also a suffix

  for(nextState = state; nextState>0; nextState--)
  {
    if(pattern[nextState-1] == ch)
    {
      for(i = 0; i<(nextState-1); ++i)
       if(pattern[i]!=pattern[state-nextState+1+i])
        break;
      if(i == nextState-1)
       return nextState;    
    }  
  }
 return 0; //Not found, nextState = 0
}
//To compute transition function which map set of input values
//to their next state
vector<vector<int>> computeTF(string pattern, int patternSize,vector<vector<int>> transFunc)
{
  int state,ch;//ch for current character
  for(state=0;state<=patternSize;++state)
   for(ch=0;ch<NO_Of_CHARS;++ch)
    transFunc[state][ch]=getNextState(pattern,patternSize,state,ch);
  return transFunc;  
}

void search(string pattern, string text)
{
  int patternSize=pattern.size();
  int textSize=text.size();

  vector<vector<int>> transFunc(patternSize+1,vector<int>(NO_Of_CHARS,0));
  
  transFunc=computeTF(pattern,patternSize,transFunc);
  
  int i,state=0;

  for(i=0;i<textSize;++i)
  {
    state=transFunc[state][text[i]];
    if(state==patternSize)
     cout<<"\nPattern found at index : "<<i-patternSize+1;
  }
}
int main()
{
  string text = "AABAACAADAABAAABAA";
  string pattern = "AABA";
  
  search(pattern,text);
  return 0;  
}