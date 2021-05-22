//Priority queue using max Heap set elements with higher value
//with higher priority
//In max heap we can delete any element but it is a priority queue
//where we can delete top element only

#include <iostream>
#include <vector>

using namespace std;

void swap(int *no1, int *no2)
{
    int temp = *no1;
    *no1 = *no2;
    *no2 = temp;
}

class PriorityQueue
{
    vector<int> array;
    int PARENT(int index)
    {
        return (index - 1) / 2;
    }
    int LEFT(int index)
    {
        return 2 * index + 1;
    }
    int RIGHT(int index)
    {
        return 2 * index + 2;
    }

    void heapifyUp(int index)
    {
        if (index != 0 && array[PARENT(index)] < array[index])
        {
            swap(&array[PARENT(index)], &array[index]);
            heapifyUp(PARENT(index));
        }
    }

    void heapifyDown(int index)
    {
        int leftChildIndex = LEFT(index);
        int rightChildIndex = RIGHT(index);
        int largest = index;

        if (leftChildIndex < size() && array[leftChildIndex] > array[index])
            largest = leftChildIndex;

        if (rightChildIndex < size() && array[rightChildIndex] > array[largest])
            largest = rightChildIndex;

        if (largest != index)
        {
            swap(&array[index], &array[largest]);
            heapifyDown(largest);
        }
    }

    //declare the functions which needs to be accessed outside as public
public:
    unsigned int size()
    {
        return array.size();
    }

    bool empty()
    {
        return size() == 0;
    }

    void push(int key)
    {
        array.push_back(key);
        int index = size() - 1;
        heapifyUp(index);
    }

    void pop()
    {
        try
        {
            if (size() == 0)
                throw out_of_range("Heap Underflow!"); //Throw custom error message
            //replace front element with last element and delete it
            array[0] = array[size() - 1]; //For implementation of priority queue
            array.pop_back();
            heapifyDown(0);
        }
        catch (const std::exception &e)
        {
            //Three types of streams cout,cin,cerr
            cerr << e.what() << '\n';
        }
    }
    int top()
    {
        try
        {
            if (size() == 0)
                throw out_of_range("Heap Underflow!");
            return array.at(0);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
};

int main()
{
    PriorityQueue pq;
    pq.push(3);
    pq.push(9);
    pq.push(10);
    pq.push(7);
    pq.push(-8);
    pq.push(30);
    pq.push(13);
    cout << "\nSize is : " << pq.size();
    cout << "\nTop : " << pq.top();
    pq.pop();
    cout << "\nAfter deleting top element, top element : " << pq.top();
    return 0;
}