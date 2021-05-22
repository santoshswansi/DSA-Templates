// Inversion count of an array using self balancing BST like AVL
// T = (n * log(n))

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//AVL node
struct node
{
    int key;                   // to store key
    int size;                  // subtree size rooted at this
    struct node *left, *right; // Left and right child pointers
    int height;                // height of the node
};

//To get new AVL node
struct node* newNode(int key)
{
    struct node *temp = new node;
    temp->key = key;
    temp->size = temp->height = 1;
    temp->left = temp->right = NULL;

    return temp;
}

int height(struct node *temp)
{
    if (temp == NULL)
        return 0;
    return temp->height;
}

int size(struct node *temp)
{
    if (temp == NULL)
        return 0;
    return temp->size;
}

//To get the balance factor
int balanceFactor(struct node *temp)
{
    if (temp == NULL)
        return 0;
    return (height(temp->left) - height(temp->right));
}

// To left rotate subtree rooted at node x
// Returns the new root of the subtree
struct node* leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    //do rotation
    y->left = x;
    x->right = T2;

    // Update subtree sizes and heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    x->size = size(x->left) + size(x->right) + 1;
    y->size = size(y->left) + size(y->right) + 1;

    return y;
}

// To right rotate subtree rooted at node y
// Returns the new root of the subtree
struct node* rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    //do rotation
    x->right = y;
    y->left = T2;

    // Update subtree sizes and heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    x->size = size(x->left) + size(x->right) + 1;
    y->size = size(y->left) + size(y->right) + 1;

    return x;
}

//Insert a new element in the AVL tree (Returns root of the tree)
//Also updates inversion count
struct node* insert(struct node *root, int key, int &result)
{
    //1. Perform normal BST operation
    if (root == NULL)
        return newNode(key);

    if (key < root->key)
    {
        root->left = insert(root->left, key, result);

        //Update result
        result += size(root->right) + 1;
    }
    else
        root->right = insert(root->right, key, result);

    //Update height and size of the ancestor node

    root->height = max(height(root->left), height(root->right)) + 1;

    root->size = size(root->left) + size(root->right) + 1;

    //Check if the tree is imbalanced
    int balance = balanceFactor(root);

    //If tree is imbalanced there are four cases
    //LEFT LEFT CASE
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);

    //RIGHT RIGHT CASE
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);

    //LEFT RIGHT CASE
    if (balance > 1 && key > root->left->key)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    //RIGHT LEFT CASE
    if (balance < -1 && key < root->right->key)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root; //Unchanged root pointer
}

int inversionCount(vector<int> array)
{
    int size = array.size();
    int result = 0;
    struct node *root = NULL;

    //Insert all elements in the tree
    for (int i = 0; i < size; ++i)
        root = insert(root, array[i], result);

    return result;
}

int main()
{
    vector<int> array = {20, 6, 5, 4, 1};

    cout << "\nInversion count = " << inversionCount(array);

    return 0;
}