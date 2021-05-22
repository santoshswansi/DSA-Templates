//Given a set of intervals and we need to do following operations 
// 1.) Add an interval
// 2.) Remove an interval
// 3.) Given an interval x, find if x overlaps any of the existing intervals

#include<iostream>

using namespace std;

//Data structure to hold interval
struct Interval
{
    int low, high;
};

//Data structure to hold a node of interval tree
struct ITNode
{
   Interval *interval;
   int max;
   ITNode *left, *right;
};

//To return new node
ITNode* newNode(Interval i)
{
    ITNode *newNode = new ITNode;
    newNode->interval = new Interval(i);
    newNode->max = i.high;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//insert
//low-value is used to maintain BST property
ITNode* insert(ITNode *root, Interval i)
{
    // tree is empty
    if(root == NULL)
     return newNode(i);

    if(root->interval->low > i.low)
      root->left = insert(root->left, i);
    else
      root->right = insert(root->right, i);

    //Update max value of this ancestor if needed
    if(root->max < i.high)
      root->max = i.high;

    return root;    
}

//To check if given 2-intervals overlap
bool doOverlap(Interval i1, Interval i2)
{
    //Just a one way of checking overlaping 
    //Whether i1 overlaps i2 or not
    if(i1.low <= i2.high && i2.low <= i1.high)
       return true;

    return false;   
}

//It searches whether there is a interval which overlap interval 'i'
Interval* overlapSearch(ITNode *root, Interval i)
{
    if(root == NULL)
     return NULL;

    //if root overlaps 'i'
    if(doOverlap(*(root->interval), i))
        return root->interval;

    //If left subtree = not empty AND
    // max(left) >= low-value of interval
    //Recur for left subtree
    if(root->left != NULL && root->left->max >= i.low)   
        return overlapSearch(root->left, i);
    
    return overlapSearch(root->right, i); 
}

//inorder traversal of the tree
void inorder(ITNode *root)
{
  if(root == NULL) 
    return;  

  inorder(root->left);
  cout<<"("<<root->interval->low<<", "<<root->interval->high<<", "
      <<root->max<<")\n";
  inorder(root->right);    
}

int main()
{
    // Let us create interval tree shown in above figure
    Interval intervals[] = {{15, 20}, {10, 30}, {17, 19}, {5, 20}, {12, 15}, {30, 40}};
    int n = sizeof(intervals)/sizeof(intervals[0]);
    ITNode *root = NULL;
    for (int i = 0; i < n; i++)
        root = insert(root, intervals[i]);

    cout<<"Inorder traversal of constructed Interval Tree : \n";
    inorder(root);

    Interval x = {6, 7};

    cout<<"\nSearching for interval ["<< x.low << "," << x.high << "]";
    Interval *res = overlapSearch(root, x);
    if(res == NULL)
        cout<<"\nNo Overlapping Interval";
    else
        cout<<"\nOverlaps with ["<< res->low << ", " << res->high << "]";

    return 0;
}