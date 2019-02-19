#ifndef DEQUE_H
#define DEQUE_H

#include <exception>

template <typename Type>
class Deque {
private:
    Type* data;
    int frontAddress = -1; //"pointers" to the front and back of the deque, incremented and decremented by inserts/removals
    int backAddress = -1;
    int sizeOfQueue = 0; //amount of objects in the queue, incremented and decremented by inserts/removals
    int capacity; //fixed size of array
public:
    Deque(int);
    ~Deque();
    bool full() const;
    bool empty() const;
    int size() const;
    Type front() const;
    Type back() const; //get back to where you once belonged
    void insertFront(Type o);
    void insertBack(Type o);
    Type removeFront();
    Type removeBack();
};

#endif