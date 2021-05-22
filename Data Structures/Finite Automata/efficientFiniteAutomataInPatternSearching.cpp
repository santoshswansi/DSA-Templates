//Efficient method of pattern searching using FINITE AUTOMATA

#include<iostream>
#include<vector>

using namespace std;
#define NO_OF_CHARS 256

//Function to make transition function matrix
vector<vector<int>> computeTF(string pattern, int patternSize,vector<vector<int>> transFunc)
{
  int i,lps=0,ch;

  //Fill 1st row(state=0) with zero except at pattern[0] 
  for(ch=0; ch<NO_OF_CHARS; ++ch)   
   transFunc[0][ch]=0;
  transFunc[0][pattern[0]]=1;

  //Fill other rows
  for(i=1; i<=patternSize; ++i) 
  {
    for(ch=0; ch<NO_OF_CHARS; ++ch) //copy values from row index of lps
     transFunc[i][ch]=transFunc[lps][ch];

    //update the entry corresponding to this character
    transFunc[i][pattern[i]]=i+1;

    //Update lps for next row to be filled
    if(i<patternSize)
     lps=transFunc[lps][pattern[i]]; 
  }

  return transFunc;  
}

void search(string pattern,string text)
{
  int patternSize=pattern.size();
  int textSize=text.size();
  
  vector<vector<int>> transFunc(patternSize+1,vector<int>(NO_OF_CHARS,0));

  transFunc = computeTF(pattern, patternSize, transFunc);

  int state=0,i;
  for(i=0; i<textSize; ++i)
  {
    state = transFunc[state][text[i]];
    if(state==patternSize)
     cout<<"\nPattern found at index : "<<i-patternSize+1;  
  } 

}

int main()
{
    string text = "AABAACAADAABAAABAA";
    string pattern = "AABA";

    search(pattern, text);
    return 0;
}