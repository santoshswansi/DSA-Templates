#include <iostream>
#include <math.h>

using namespace std;

#define MIN_TABLE_SIZE 10

//To store type of node to facilitate deleting node
//It will help us in finding node
enum NodeType
{
    Legitimate,
    Empty,
    Deleted
};

//A node in hash table
struct HashNode
{
    int key;
    NodeType info;
};

//HashTable to store multiple HashNode
struct HashTable
{
    int size;
    HashNode *table;
};

bool isPrime(int num)
{
    if (num == 2 || num == 3)
        return true;
    if (num == 1 || num % 2 == 0)
        return false;
    for (int i = 3; i * i <= num; i += 2)
        if (num % i == 0)
            return false;
    return true;
}

int nextPrime(int num)
{
    if (num <= 0)
        num = 3;
    if (num % 2 == 0)
        num++;
    for (; !isPrime(num); num += 2)
        ;
    return num;
}

int HashFunction(int key, int size)
{
    return key % size;
}

HashTable *initialiseHashTable(int size)
{
    HashTable *hashTable;
    if (size < MIN_TABLE_SIZE)
    {
        cout << "\nTable size is too low!";
        return NULL;
    }
    hashTable = new HashTable; //create new hashtable
    if (hashTable == NULL)
    {
        cout << "\nOut of space!";
        return NULL;
    }
    hashTable->size = nextPrime(size);
    hashTable->table = new HashNode[hashTable->size];
    if (hashTable->table == NULL)
    {
        cout << "\nTable size is too small!";
        return NULL;
    }
    for (int i = 0; i < hashTable->size; ++i)
    {
        hashTable->table[i].info = Empty; //1
        hashTable->table[i].key = 0;
    }
    return hashTable;
}

//If key is present : search() will return index of node in the HashTable
//Else it will return index of node where it is free (For Insertion)
//It will also handle key redundancy
int search(int key, HashTable *hashTable)
{
    int index = HashFunction(key, hashTable->size);
    int counter=1;
    while (hashTable->table[index].info != Empty &&
           hashTable->table[index].key != key)
    {
        index = (index + (int)pow(counter,2)) % hashTable->size;
        if (hashTable->table[index].key == key)
            return index;
    }
    return index;
}

void insert(int key, HashTable *hashTable)
{
    int index = search(key, hashTable);
    if (hashTable->table[index].info != Legitimate)
    {
        hashTable->table[index].key = key;
        hashTable->table[index].info = Legitimate;
        cout<<"\n"<<key<< " inserted!";
    }
}

//function to rehash the HashTable (Increases the size of the HashTable)
HashTable *rehash(HashTable *hashTable)
{
    int size = hashTable->size;
    HashNode *table = hashTable->table;
    hashTable = initialiseHashTable(2 * size);
    for (int i = 0; i < size; ++i)
    {
        if (table[i].info == Legitimate)
            insert(table[i].key, hashTable);
    }
    free(table);
    return hashTable;
}

void retrieve(HashTable *hashTable)
{
    for (int i = 0; i < hashTable->size; ++i)
    {
        int key = hashTable->table[i].key;
        if (!key)
            cout << "\nPosition : " << i + 1 << " Element : NULL";
        else
            cout << "\nPosition : " << i + 1 << " Element : " << key;
    }
}

void remove(int key, HashTable *hashTable)
{
    int index = search(key, hashTable);
    if (hashTable->table[index].info == Legitimate)
    {
        hashTable->table[index].info = Deleted;
        hashTable->table[index].key = 0;
        cout << "\n"
             << key << " deleted!";
    }
    else
        cout << "\n"
             << key << " not deleted!";
}

int main()
{
    HashTable *hashTable;
    int key;
    int size;
    int choice;
    int currTotElem = 1;
    while (1)
    {
        cout << "\nCHOOSE ONE OPTION :-";
        cout << "\n1.Initialise the size of the table";
        cout << "\n2.Insert";
        cout << "\n3.Delete";
        cout << "\n4.Display";
        cout << "\n5.Rehash the table";
        cout << "\n6.EXIT\n";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nEnter the size of the table : ";
            cin >> size;
            hashTable = initialiseHashTable(size);
            cout << "\nSize of the table : " << nextPrime(size);
            break;
        case 2:

            if (currTotElem > hashTable->size)
            {
                cout << "\nHash table is full, rehash the hash table.";
                continue;
            }
            cout << "\nEnter the element to be inserted : ";
            cin >> key;
            insert(key, hashTable);
            ++currTotElem;
            break;
        case 3:
            if (hashTable->size == 0)
            {
                cout << "\nHashTable Underflow!";
                continue; //continue with the next step
            }
            cout << "\nEnter the element to be deleted : ";
            cin >> key;
            remove(key, hashTable);
            break;
        case 4:
            retrieve(hashTable);
            break;
        case 5:
            hashTable = rehash(hashTable);
            break;
        case 6:
            exit(1);
        default:
            cout << "\nWrong option!";
        }
    }
    return 0;
}