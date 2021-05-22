#include<iostream>
#include<vector>
#include<algorithm>

using  namespace std;

void bucketSort(float numbers[],int size)
{
 //for numbers in the range of 0.0 and 1.0   
 const int s=size;
 vector<vector<float>> buckets(s);
 int i,j,k=0;

 for(i=0;i<size;++i)
 {
  int bIndex=size*numbers[i];   
  buckets[bIndex].push_back(numbers[i]); 
 }

 for(i=0;i<size;++i)
  sort(buckets[i].begin(),buckets[i].end());

 for(i=0;i<size;++i)
  for(j=0;j<buckets[i].size();++j)
   numbers[k++]=buckets[i][j];
  
}
void display(float numbers[],int size)
{
 for(int i=0;i<size;++i)
  printf("%f, ",numbers[i]);
}
int main()
{
   float numbers[]={0.123,0.115,0.172,0.121,0.512,0.846,0.981,0.417,0.212,0.112,0.412,0.74,0.773,0.098990};
   const int size=sizeof(numbers)/sizeof(numbers[0]);
   printf("\nBefore sorting : ");
   display(numbers,size);
   bucketSort(numbers,size);
   printf("\nAfter sorting : ");
   display(numbers,size);
   return 0;  
}