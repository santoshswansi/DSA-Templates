// Find a^b (mod c) 
// T = O(Log(b))
//Recursive Implementation

#include<iostream>

using namespace std;

int modular_power(int a, int b, int c)
{
  if(a == 0)
   return 0;

  if(b == 0)
   return 1%c;

  long result;

  //If b : even
  if(b%2 == 0)
  {
      result = modular_power(a, b/2, c)%c;
      result = (result*result)%c;
  }  

  //If b : odd
  else
  {
      result = a*(modular_power(a, b/2, c)%c )%c;
      result = (result*result)%c;
  }
  
  return (result + c)%c; //To handle -ve value of 'result'
}

int main()
{
    int a = 3, b = 4, c = 6;
    cout<<"modular_power("<<a<<", "<<b<<", "<<c<<") = "<<modular_power(a, b, c);
    return 0;
}