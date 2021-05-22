//Given an array of patterns that we want to search from the text
//We can create a Finite state machine 

//It has mainly three functions

//1. goTo[][] 
//            --> It simply follow edges of Trie of all words in array[]
//            --> Store next_state for current_state and character
//            --> We build Trie
//            --> For all characters which do not have an edge to root,
//                 we add  edge back to root

//2. failure[] 
//             --> Stores all edges that are followed when current 
//                 character does not have edge in Trie
//             --> Store next state from current state  
//             --> For a state s, we find the longest proper suffix which
//                 is a proper prefix of some pattern
//             --> Made using Breadth First Traversal of Trie

//3. output[]
//           -->  Stores indexes of all words that end at current state
//           -->  Store indexes of all matching words as a bitmap for
//                current state (by doing bitwise OR of values)
//           -->  Computed using Breadth First Traversal with failure

#include<iostream>
#include<string.h>
#include<queue>

using namespace std;

//max number of states(= sum of length of all keywords)
const int MAXS = 500;
const int MAXC = 26; //max number of characters in input alphabets

int out[MAXS]; //output function
int f[MAXS]; // failure function
int goTo[MAXS][MAXC]; //goto Function(TRIE)

//This function builds the string matching machine 
//array[] --> Array of words. The index of each keyword is important!
//            "out[state] & (1<<i)" > 0 (if keyword is present)
//Returns number of states 

int buildMatchingMachine(string array[], int totPatterns)
{
    //Initialise out[] & goTo[] to 0 and -1
    memset(out, 0, sizeof(out));
    memset(goTo, -1, sizeof(goTo));

    int states = 1; //Initially we have just state-0(root)

    //construct goTo[][] {Same as building TRIE for array[]}
    for (int i = 0; i <totPatterns; ++i)
    {
        const string &word = array[i];
        int currentState = 0;
        int wordLength = word.length();
        for(int j = 0; j < wordLength; ++j)
        {
            int ch = word[j] - 'a';

            //Allocate a new node(create a new state)
            //If a node for ch does not exist
            if(goTo[currentState][ch] == -1)
               goTo[currentState][ch] = states++;
            currentState = goTo[currentState][ch];   
        }
        out[currentState] |= (1<<i);
    }

    //For all characters which do not have an edge from root(state = 0)
    // int TRIE, add a goto edge to state 0
    for(int ch = 0 ; ch < MAXC; ++ch)
      if(goTo[0][ch] == -1)
        goTo[0][ch] = 0;

    //Build the failure function
    memset(f, -1, sizeof(f)); //Initialise f[] with -1

    //Failure function is computed in breadth first order using queue
    queue<int> queue; 

    //Iterate over every possible input
    for(int ch = 0; ch < MAXC; ++ch) 
    {
        //All nodes of depth = 1 have failure function value = 0
        if(goTo[0][ch] != 0)
        {
            f[goTo[0][ch]] = 0;
            queue.push(goTo[0][ch]);
        }  
    }  
    
    while(queue.size())
    {
      //Remove front state from queue
      int state = queue.front();
      queue.pop();

      //For the removed state, find failure function for all 
      //those characters for which goTo function is not defined
      for(int ch = 0; ch <= MAXC; ++ch)
      {
          //If goTo function is defined for character 'ch' and 'state'
          if(goTo[state][ch] != -1)
          {
              //Find failure state of removed state
              int failure = f[state];

              while(goTo[failure][ch] == -1)
              {
                  failure = f[failure];
              }

              failure = goTo[failure][ch];
              f[goTo[state][ch]] = failure;

              //Merge output values
              out[goTo[state][ch]] |= out[failure]; 

              //Insert the next level node(of TRIE) in queue
              queue.push(goTo[state][ch]);  
          }
      }
    }
    return states;
}

//Returns the next state the machine will transition to using goTo &
//failure functions
//nextInput = the character that enters into the machine
int findNextState(int currentState, char nextInput)
{
    int answer = currentState;
    int ch = nextInput - 'a';

    //While goTo[][] is not defined use f[]
    while(goTo[answer][ch] == -1)
    {
        answer = f[answer];
    }  
   
    return goTo[answer][ch];  
}

void searchedWords(string array[], int totPatterns, string text)
{
    buildMatchingMachine(array, totPatterns);

    int currentState = 0;
    //int textSize = text.size();


    //Traverse through the text
    for(int i = 0; i < text.size(); ++i)
    {
        currentState = findNextState(currentState, text[i]);

        //If match not found, move to next state
        if(out[currentState] == 0)
          continue;

        //Match found, print all matching words of arr[] using o[]
        for(int j = 0; j < totPatterns; ++j)
        {
            if(out[currentState] & (1<<j))
            {
                cout<<"\nWord : "<<array[j]<<" ["
                    <<i-array[j].size()+1<<", "<<i<<"].";
            }
        }  
    }

}

int main()
{
    string array[] = {"he","his","she","hers"};
    string text = "ahishers";
    int totPatterns = sizeof(array)/sizeof(array[0]);
    searchedWords(array, totPatterns, text);
    return 0;
}
