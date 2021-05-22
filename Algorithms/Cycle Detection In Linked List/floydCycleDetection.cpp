// Given a linked list find whether it contains cycle or not
// METHOD - 1 : Using Floyd Cycle Detection
// T = O(n)

#include <iostream>

using namespace std;

struct Node
{
    int data;
    Node *next;
};

Node *start; //To store starting node of the cycle in linked list if exist

Node *newNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->next = NULL;
    return node;
}

//To find start node of the cycle of the linked list when we figured out
//that the linked list contains cycle
void findStartNode(Node *slow, Node *fast)
{
    //Move fast and slow pointers by 1 
    while(1)
    {
        if(slow == fast)
        {
            start = slow;
            return;
        }

        slow = slow->next;
        fast = fast->next;  
    }
}

bool detectCycle(Node *root)
{
    Node *slow = root, *fast = root;

    //Traverse the list
    while (fast && fast->next)
    {
        //Move slow pointer by 1 node
        slow = slow->next;

        //Move fast pointer by 2 nodes
        fast = fast->next->next;

        //If they meet
        if(slow == fast)
        {
            //Find the start node
            findStartNode(root, fast);
            return true;
        }
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

    if (detectCycle(root))
        cout << "\nCycle present starting from node : " << start->data;
    else
        cout << "\nCycle not present!";

    return 0;
}
