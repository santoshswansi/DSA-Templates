#include<iostream>
#include<vector>

using namespace std;

vector<int> countingSort(vector<int> numbers)
{
  //If the  numbers are in the range 1-10
  vector<int> count(11,0);
  int size=numbers.size();
  int i;
  int k=0;
  for(i=0;i<size;++i)
   count[numbers[i]]++;

  for(i=0;i<size;)
  {
   while(count[k]!=0)
   {
    numbers[i]=k;
    ++i;
    --count[k];
   } 
   ++k;
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
   vector<int> numbers={1,5,2,1,5,10,1,4,2,1,4,4,3,9,2,1,2,2,8,3,4,2};
   printf("\nBefore sorting : ");
   display(numbers);
   numbers=countingSort(numbers);
   printf("\nAfter sorting : ");
   display(numbers);
   return 0; 
}