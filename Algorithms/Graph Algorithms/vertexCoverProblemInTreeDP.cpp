//Find the minimum vertex cover in a Binary Tree
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

struct Node
{
    int data;
    int vertexCover; //Vertex cover rooted at this vertex
    Node *left, *right;
};

Node* newNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->vertexCover = 0;
    node->left = node->right = NULL;
    return node;
}

int t1, t2;

int vCover(Node *root)
{
    if(root == NULL)
      return 0;
    if(root->left == NULL && root->right == NULL)
      return 0; 

    //SUBPROBLEM : vertex cover at particular vertex as a root
    //If subproblem is already calculated
    if(root->vertexCover != 0)
      return root->vertexCover;

    int rootIncluded = 1 + vCover(root->left) +vCover(root->right);

    int rootExcluded = 0;
    if(root->left != NULL)
        rootExcluded += 1 + vCover(root->left->left) + vCover(root->left->right);
  
    if(root->right != NULL) 
        rootExcluded += 1 + vCover(root->right->left) + vCover(root->right->right);
    
    root->vertexCover = min(rootIncluded, rootExcluded);

    t1 = rootIncluded, t2 = rootExcluded;
    return root->vertexCover;      
}

int main()
{
    //Binary tree
    Node *root = newNode(10);
    root->left = newNode(20);
    root->right = newNode(30);
    root->left->left = newNode(40);
    root->left->right = newNode(50);
    root->right->right = newNode(60);
    root->left->right->left = newNode(70);
    root->left->right->right = newNode(80);
    
    //Find the vertex cover 
    cout<<"Vertex Cover : "<<vCover(root)<<endl;
    cout<<t1<<" "<<t2<<endl;
    return 0;
}