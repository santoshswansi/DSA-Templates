// power(x, y) 
// where x can be a floating-point value and y can be negative

#include<iostream>

using namespace std;

float power(float x, int y)
{
   if(y == 0)
    return 1;

  float temp = power(x, y/2);

  if(y%2 == 0)
     return temp*temp;
  else
  {
      if(y > 0)
          return x*temp*temp;
      else
          return temp*temp/x;   // negative value of y 
          
   }  
       
}

int main()
{
    float x = 2.5;
    int y = 2;
    cout<<"power(2.5, 2) = "<<power(x,y)<<endl;

    x = 2.5;
    y = -2;
    cout << "power(2.5, -2) = " << power(x, y) << endl;

    x = 2;
    y = -2;
    cout << "power(2, -2) = " << power(x, y) << endl;

    return 0;
}