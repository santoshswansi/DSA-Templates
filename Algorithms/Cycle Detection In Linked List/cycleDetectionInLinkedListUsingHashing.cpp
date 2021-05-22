// Given a linked list find whether it contains cycle or not
// METHOD - 1 : Using Hashing
// T = O(n)

#include<iostream>
#include<unordered_set>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *start; //To store starting node of the cycle in linked list if exist

Node* newNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->next = NULL;
    return node;
}

bool detectCycle(Node *root)
{
    Node *curr = root;
    unordered_set<Node*> set; 

    //Traverse the list
    while(curr)
    {
        //Return true if we already seen this node before
        if(set.find(curr) != set.end())
        {
            start = curr;
            return true;
        }   

        //Insert current node into the set
        set.insert(curr);

        //Move to the next node
        curr = curr->next;  
    }
    return false;
}

int main()
{
    Node *root = newNode(1);
    root->next = newNode(2);
    root->next->next = newNode(3);
    root->next->next = newNode(4);
    root->next->next->next = root->next; //Inserting cycle in the linked list
    
    if(detectCycle(root))
       cout<<"\nCycle present starting from node : "<<start->data;
    else
       cout<<"\nCycle not present!";
       
    return 0;
}
