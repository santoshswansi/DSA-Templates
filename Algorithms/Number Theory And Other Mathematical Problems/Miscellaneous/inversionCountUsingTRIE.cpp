// Inversion Count Using TRIE
// T = (n * log(n))

#include<iostream>
#include<vector>

using namespace std;

//Node of the TRIE
struct node
{
    int count; // Total numbers of numbers visited this node
    node *left, *right;
};

node* newNode()
{
    node *temp = new node;
    temp->count = 1;
    temp->left = temp->right = NULL;
    return temp;
}

//Insert element into the TRIE
void insert(int num, node *root, int &result)
{
    //Converting the number in binary form
    //Assuming numbers are stored in 64 bits
    for(int i = 63; i>=0; --i)
    {
        //i-th bit is set or not
        int a = ( num & (1<<i) );

        //If ith bit is set
        if(a != 0)
        {
           //If left node exist then there are numbers less than
           // current number . Count those using 'count' and add to 
           // the result
           if(root->left != NULL)
           {
               result += root->left->count;
           }

           //Move to the right
           if(root->right != NULL)
           {
             root = root->right;
             root->count +=1;
           }
           else
           {
             node *temp = newNode();
             root->right = temp;
             root = root->right;  
           }
        }
        else
        {
          //i-th bit is not set
          if(root->left != NULL)
          {
            root = root->left;
            root->count += 1;
          }   
          else
          {
            node *temp = newNode();
            root->left = temp;
            root = root->left; 
          }
        }
    }
}

int inversionCount(vector<int> array)
{
    int size = array.size();
    int result = 0;

    node *root = newNode();

    //Insert from right to left
    for(int i = size-1; i >= 0; --i)
    {
        insert(array[i], root, result);
    }
  return result;
}

int main()
{
    vector<int> array = {20, 6, 5, 4, 1};

    cout << "\nInversion count = " << inversionCount(array);

    return 0;
}