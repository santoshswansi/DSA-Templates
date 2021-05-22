#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int binarySearch(vector<int> array,int key,int start,int end)
{
  cout<<"k";  
  int middle=(start+end)/2;
  if(array[middle]==key)
   return middle;

  if(array[middle]<key)
   return binarySearch(array,key,middle+1,end); //you should must write return if there is a return type
  else
   return binarySearch(array,key,start,middle-1);
  return -1; 
}
int main()
{
  int size;
  int num;
  int key;
  vector<int> array(10);
  cout<<"\nTotal elements : ";
  cin>>size;
  array.resize(size);
  cout<<"\nEnter "<<size<<" elements : ";
  for(int i=0;i<size;++i)
  {
      cin>>num;
      array[i]=num;
  }  
  cout<<"\nElement that you want to search : ";
  cin>>key;
  sort(array.begin(),array.end());
  int index=binarySearch(array,key,0,size);
  if(index!=-1)
   cout<<"\n"<<key<<" is indexed at (index can be found after sorting) "<<index;
  else
   cout<<"\nElement not found!";
   
  return 0;  
}