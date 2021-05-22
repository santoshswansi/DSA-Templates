//Huffman Coding is a file size compression technique for a message having
//multiple occurrences of single characters
//_______________________________________________________________________
//PROBLEM STATEMENT : Given a list of characters and their frequencies
//                   find the huffman codes of them
//T = (nlog(n))  

#include<iostream>

using namespace std;

//You can avoid this constant by explicitely calculating height 
//of the huffman tree
#define MAX_HUFFMANTREE_HEIGHT 100

//Data structure to store node of min heaph 
struct MinHeapNode
{
    unsigned count;
    char data;
    MinHeapNode *left, *right;
};

struct MinHeap
{
    unsigned currSize; // current size of min heap
    unsigned capacity; // maximum no. of elements that it can store
    struct MinHeapNode **array; // Array of MinHeaphNode pointers
};

//returns new min heap node
MinHeapNode* newNode(char data, unsigned count)
{
    MinHeapNode *node = new MinHeapNode;
    node->data = data;
    node->count = count;
    node->left = node->right = NULL;
    
    return node;
}

//create min heap of given capacity
MinHeap* createMinHeap(int capacity)
{
    MinHeap *minHeap = new MinHeap;
    minHeap->currSize = 0;
    minHeap->capacity = capacity;
    minHeap->array = new MinHeapNode*[capacity];

    return minHeap;
}

void swapMinHeapNode(MinHeapNode **node1, MinHeapNode **node2)
{
    MinHeapNode *temp = *node1;
    *node1 = *node2;
    *node2 = temp;
}

void minHeapify(MinHeap *minHeap, int index)
{
    int smallest = index;
    int left = index*2 + 1;
    int right = index*2 + 2;

    if(left < minHeap->currSize && minHeap->array[left]->count
                                <  minHeap->array[smallest]->count)
          smallest = left;

    if (right < minHeap->currSize && minHeap->array[right]->count 
                                   < minHeap->array[smallest]->count)
        smallest = right;

    //Now smallest of three is stored in smallest
    if(smallest != index)
    {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
        minHeapify(minHeap, smallest);
    }
}

//To delete root node and return root node from min heap
MinHeapNode* extractMin(MinHeap *minHeap)
{
    MinHeapNode *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->currSize - 1];
    minHeapify(minHeap, 0);
    --minHeap->currSize;
    
    return temp;
}

//Insert a minHeapNode in the min heap
void insertMinHeapNode(MinHeap *minHeap, MinHeapNode *node)
{ 
    ++minHeap->currSize;
    int i  = minHeap->currSize -1;

    // if i-1 is the last index  then parent of it can  be found at index
    // (i-1)/2
    
    while(i != 0 && node->count < minHeap->array[(i-1)/2]->count)
    {
        minHeap->array[i] = minHeap->array[(i-1)/2];
        i = (i-1)/2;
    }
    minHeap->array[i] = node;
}

//Standard function to build min heap
void buildMinHeap(MinHeap *minHeap)
{
    int size = minHeap->currSize;
    int i;
    for ( i = (size-1)/2; i >= 0; --i)
      minHeapify(minHeap, i);
}

//Create + Build min heap
MinHeap* createAndBuildMinHeap(char *datas, int *counts, int size)
{
    //Create min heap
    MinHeap *minHeap = createMinHeap(size);

    for(int i = 0; i < size; ++i)
          minHeap->array[i] = newNode(datas[i], counts[i]);

    //Initially currSize = size 
    minHeap->currSize = size;

    //Build min heap
    buildMinHeap(minHeap);

    return minHeap;       
}

bool  isSizeOne(MinHeap *minHeap)
{
    return minHeap->currSize == 1;
}

//Function to build huffman tree and return root of it
MinHeapNode*  buildHuffmanTree(char datas[], int counts[], int size)
{
    MinHeapNode *top, *left, *right;

    //STEP 1 : Create a min_heap node of capacity = size
    //Initially number of nodes = size
    MinHeap *minHeap = createAndBuildMinHeap(datas, counts, size);


    //Iterate through min_heap while its currSize != 1
    while(!isSizeOne(minHeap))
    {
        //STEP 2 : Extract to min count characters from min_heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        //STEP 3 : Create a new internal node with frequency = sum
        // of frequencies of last two min-frequency nodes in min_heap
        //Add this node to the min_heap
        //'$' is a special value for internal nodes, not used in message
        top = newNode('$', left->count + right->count);
        top->left = left;
        top->right = right;
        insertMinHeapNode(minHeap, top);
    }

    //STEP 4 :  The remaining node = root node & huffman tree is complete
    return extractMin(minHeap);
}

//Prints elements in array
void printArr(int *arr, int size)
{
    for(int i = 0; i < size; ++i)
     cout<<arr[i];
    cout<<endl; 
}

//Print huffman codes from the root of Huffman tree
//It uses arr[] to store code
void printCodes(MinHeapNode *root,  int arr[], int top)
{
  //Assign 0 to left edge & recur
  if(root->left)
  {
      arr[top] = 0;
      printCodes(root->left, arr, top+1);
  }

  //Assign 1 to right edge & recur
  if(root->right)
  {
      arr[top]= 1;
      printCodes(root->right, arr, top+1);
  }

  //NOTE : Only leaf node contains unique characters of message
  if(root->left == NULL && root->right == NULL)
  {
      printf("%c : ",root->data);
      printArr(arr, top); //Top = stores size OR height
  }
}

void huffmanCodes(char datas[], int counts[], int size)
{
    //Construct Huffman Tree
    MinHeapNode *root = buildHuffmanTree(datas, counts, size);

    //Print huffmanCodes using Huffman Tree
    //arr stores huffman codes of input characters
    int arr[MAX_HUFFMANTREE_HEIGHT], top = 0;
    printCodes(root, arr, top);
}

int main()
{
    char datas[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int counts[] = {5, 9, 12, 13, 16, 45};

    int size = sizeof(datas)/sizeof(datas[0]);

    huffmanCodes(datas, counts, size);
  
    return 0;
}