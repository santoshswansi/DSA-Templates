#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int max(vector<int> array)
{
  int size=array.size();
  int max=array[0];
  for(int i=1;i<size;++i)
  {
    if(array[i]>max)
     max=array[i];
  }
 return max;
}

vector<int> countingSort(vector<int> numbers,int exp)
{
 const int size=numbers.size();
 vector<int> output(size);
 vector<int> count(10,0);
 int i;
 for(i=0;i<size;++i)
  count[(numbers[i]/exp)%10]++;

 for(i=1;i<size;++i)
  count[i]+=count[i-1];

 for(i=size-1;i>=0;--i)
 {
   output[count[(numbers[i]/exp)%10]-1]=numbers[i];
   count[(numbers[i]/exp)%10]--;
 }   
 for(i=0;i<size;++i)
  numbers[i]=output[i];

 return numbers; 
}

vector<int> radixSort(vector<int> numbers)
{
  int maxElem=max(numbers);
  for(int exp=1;maxElem/exp>0;exp*=10)
   numbers=countingSort(numbers,exp);

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
   numbers=radixSort(numbers);
   cout<<"\nAfter sorting : ";
   display(numbers);
   return 0;   
 return 0;
}