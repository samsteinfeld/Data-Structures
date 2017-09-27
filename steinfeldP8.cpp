/*
 * Sam Steinfeld
 *
 * File   : steinfeldP8.cpp
 * Purpose: To add or remove add items from a queue as specified by the user
 * Input  : 'e' for enter, 'd' for dequeue or 'q' for quit. If the user selects dequeue,
 *          they choose how many items they would like to dequeue.
 * Output : The remaining items in the queue
 */

#include <iostream>
#include <iomanip>
#include <assert.h>

using namespace std;

const int MAX = 100; // max amount of numbers in queue

class Queue
{
public:
    bool empty() const; // determines if queue is empty
    bool full() const; // determines if queue is full
    int front(); // returns the first element of the queue
    void enqueue(const int& x); // adds 'x' to the queue
    void dequeue(); // removes the first element from the queue
    Queue(); // constructor
protected:
    int maxQueueSize; // max size of queue
    int count; // keeps count of number of items in queue
    int queueFront; // points to first element of queue
    int queueRear; // points to last element of queue
    int *list; // pointer to the array that holds the queue elements
};

class mikeQ : public Queue
{
public:
    void enMike(const int& x); // adds element to the front of the queue if it is
                               // 10 or greater than the current first element
    void deMike(const int& x); // removes the number of elements the user specifies
                               // from the queue
};

bool Queue::empty() const
// Postcondition: Returns true if queue is empty, otherwise, returns false
{
    return (count == 0);
}

bool Queue::full() const
// Postcondition: Returns true if queue is full, otherwise, returns false
{
   return (count == maxQueueSize);
}

int Queue::front()
//Precondition: The queue exists and is not empty
//Postcondition: If the queue is empty, the program terminates; otherwise, the first
// element of the queue is returned
{
    assert (!empty());
    return list[queueFront];
}

void Queue::enqueue(const int& x)
//Precondition: The queue exists and is not full.
//Postcondition: The queue is changed and x is added to the queue.
{
    if (!full())
    {
        queueRear = (queueRear + 1) % maxQueueSize;
        count++;
        list[queueRear] = x;
    }
    else
        cout << "Cannot add to a full queue." << endl;
}

void Queue::dequeue()
//Precondition: The queue exists and is not empty.
//Postcondition: The queue is changed and the first element is removed from the queue.
{
    if (!empty())
    {
        count--;
        queueFront = (queueFront + 1) % maxQueueSize;
    }
    else
        cout << "Cannot remove from an empty queue." << endl;
}

Queue::Queue()
// Postcondition: initializes values of maxQueueSize to MAX(100), queueFront 0,
// queueRear to the end of the queue (99), count to 0, and list as an array
// with a max storage of 100
{
    maxQueueSize = MAX;

    queueFront = 0;
    queueRear = maxQueueSize - 1;
    count = 0;
    list = new int[maxQueueSize];
}

void mikeQ::enMike(const int& x)
//Precondition: The queue exists and is not full.
//Postcondition: The queue is changed and x is added to the front of
// the queue if it is greater than the current first element, otherwise, the element
// is added to the rear
{
    if (x >= (list[queueFront] + 10)){
        if (!full())
        {
            if (queueFront > 0)
                queueFront = (queueFront - 1);
            else
                queueFront = maxQueueSize - 1;

            count++;
            list[queueFront] = x;
        }
        else
            cout << "Cannot add to a full queue." << endl;
    }

    else
        enqueue(x);
}

void mikeQ::deMike(const int& x)
//Precondition: The queue exists and is not empty.
//Postcondition: The queue is changed and the number of elements the user
// specifies (x) is removed from the queue.
{
    if (!empty())
    {
        count -= x;
        queueFront = (queueFront + x) % maxQueueSize;
    }

    else
        cout << "Cannot remove from an empty queue." << endl;
}

int main () {
    mikeQ q; // create a Mike queue
    int item; // item to add to queue
    char ch; // character code
    int x; //number of items the user wishes to dequeue

    cout << "Enter e(nter), d(equeue), or q(uit): ";
    cin >> ch;

    while (ch != 'q') {
        if (ch == 'e')
            if (!q.full()) {
                cout << "number: ";
                cin >> item;
                q.enMike (item);
        } else
            cout << "Error - queue is full" << endl;
        else if (ch == 'd')
            if (!q.empty()){
                cout << q.front() << endl;
                cout << "Please enter the number of items you'd like to remove from the queue: ";
                cin >> x;
                q.deMike(x);
            } else
                cout << "Error - empty queue" << endl;
        else
            cout << "Error in code - ignored" << endl;

        cout << "Enter e(nter), d(equeue), or q(uit): ";
        cin >> ch;
        }

    cout << endl << "Numbers remaining in queue: " ;
    if (q.empty())
        cout << "None";

    while (!q.empty())
    {
        cout << q.front() << " ";
        q.deMike(1);
    }
    cout << endl;
        return 0;
}
