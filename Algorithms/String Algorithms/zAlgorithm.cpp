//Searching pattern in text using z-array of text[]
//Z[i]-> Longest prefix starting from text[i] which is also prefix of text

#include<iostream>
#include<string.h>

using namespace std;

void fillZArray(string text, int zArray[], int textSize);

void search(string text, string pattern)
{
    int patLength = pattern.length();

    // $ sign is not accepted in either of pattern or text
    string concatenatedText = pattern + "$" + text;
    int length = concatenatedText.length();
    
    int *zArray = new int[length];

    fillZArray(concatenatedText, zArray, length);

    //Search for z-value = patSize
    for(int i = 1; i < length; ++i)
    {
        if(zArray[i] == patLength)
         cout<<"\nPattern found at index : "<<i-(patLength+1);
    }
}

void fillZArray(string text, int *zArray, int textSize)
{
    int L, R; //[L,R] -> makes a window which matches with prefix of text
    int k;

    L = R = 0;
    

    for(int i = 1; i < textSize; ++i)
    {
        //If i>R nothing matches -> calculate zArray[] using naive way
        if(i > R)
        {
            L = R = i;

            while(R < textSize && text[R-L] == text[R])
               ++R;
            zArray[i] = R-L;
            --R;   
        }
        else
        {
            // k = i-L 
            //It corresponds to number which matches in [L,R] interval
            //to the prefix of text
            k = i - L;

            //If (zArray[k] < remaining interval)--> zArray[i] = zArray[k]
            if(zArray[k] < R-i+1)
              zArray[i] = zArray[k];
            else
            {
                //Expansion of [L,R] possible
                L = i;
                while (R < textSize && text[R-L] == text[R])
                  ++R;
                zArray[i] = R - L;
                --R;  
            }
        }
    }  
}
int main()
{
    string text = "ABABDASEAVAEDAWEVABAAABAFV";
    string pattern = "AB";
    search(text, pattern);
    return 0;
}