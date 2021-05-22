#include<iostream>
#include<vector>

using namespace std;

vector<int> shellSort(vector<int> numbers)
{
  int size=numbers.size(); 
  int j;
  for(int gap=size/2;gap>0;gap/=2)
  {
    for(int i=gap;i<size;++i)
    {
      int temp=numbers[i];
      for(j=i; j>=gap && numbers[j-gap]>temp;j-=gap)
       {
          numbers[j]=numbers[j-gap];
       }
       numbers[j]=temp;
    } 
  }
  return numbers;
}

void display(vector<int> numbers)
{
  int size=numbers.size();
  for(int i=0;i<size;++i)
   printf("%d, ",numbers[i]);
}

int main()
{
   vector<int> numbers={1,87,27,3,7,5,19,100,13,0};
   const int size=numbers.size();
   cout<<"\nBefore sorting : ";
   display(numbers);
   numbers=shellSort(numbers);
   cout<<"\nAfter sorting : ";
   display(numbers);
   return 0;   
 return 0;
}