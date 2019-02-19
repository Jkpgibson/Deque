#include "Deque.h"
#include <stdexcept>
#include <iostream>
 
template class Deque<int>;

template <typename Type>
Deque<Type>::Deque(int n)
{
    capacity = n;
    data = new Type[n];
}

template <typename Type>
Deque<Type>::~Deque(){}

template <typename Type>
bool Deque<Type>::empty() const
{
    return frontAddress == -1;
}

template <typename Type>
bool Deque<Type>::full() const
{
    return ((frontAddress == 0 && backAddress == capacity - 1) || (frontAddress == backAddress + 1)); //account for wrap-around and for straightforward full
}

template <typename Type>
int Deque<Type>::size() const
{
    return sizeOfQueue;
}

template <typename Type>
Type Deque<Type>::front() const
{
    return data[frontAddress];
}

template <typename Type>
Type Deque<Type>::back() const
{
    return data[backAddress];
}

template <typename Type>
void Deque<Type>::insertFront(Type elem)
{
    if (full()) {
        std::cout << "Front Overflow" << '\n'; //cannot insert into a full queue, and sizeOfQueue is not dynamic
        return;
    }

    //set frontAddress to point to an empty space in the array before insertion
    if (frontAddress == -1) {   //queue is empty at insertion
        frontAddress = 0;
        backAddress = 0;
    } 
    else if (frontAddress == 0) { //wrap frontAddress around to the backAddress for circularity
        frontAddress = capacity - 1; 
    }
    else {                //frontAddress gets "pushed up" if it's not at the beginning of the array
        frontAddress--; 
    }

    data[frontAddress] = elem;   //insert element into Deque 
    sizeOfQueue++;               //increment sizeOfQueue with every insertion
}

template <typename Type>
void Deque<Type>::insertBack(Type elem)
{
    if (full()) {
        std::cout << "Back Overflow" <<'\n';
        return;
    }
    //set backAddress to point to an empty space in the array before insertion
    if (backAddress == -1) {                   //queue is empty at insertion
        backAddress = 0;
        frontAddress = 0;
    }
    else if (backAddress == sizeOfQueue-1) {  //wrap around for circularity
        backAddress = 0;
    }
    else {                                    //backAddress gets "pushed backAddress" if it's not at the end of the array
        backAddress++;
    }

    data[backAddress] = elem;          //insert element into Deque
    sizeOfQueue++;                     //increment sizeOfQueue with every insertion
}

template <typename Type>
Type Deque<Type>::removeFront()
{
    if (empty()) {
        throw std::runtime_error("Front Underflow");
    }

    Type temp = data[frontAddress]; //element at frontAddress at the time of removal

    //reset frontAddress pointer to the next in line
    if (frontAddress == backAddress){           //only one element left in queue
        frontAddress = -1;
        backAddress = -1;
        sizeOfQueue = 0;
    }
    else {
        if (frontAddress == sizeOfQueue-1){    //frontAddress is at the end of the array, and must be wraped around for circularity
            frontAddress = 0;
            sizeOfQueue--;
        }
        else {                                 //frontAddress is at the start or anywhere else
            frontAddress++;
            sizeOfQueue--;
        }
    }
    return temp;                                //return the element that was at the frontAddress
}

template <typename Type>
Type Deque<Type>::removeBack()
{
    if (empty()) {
        throw std::runtime_error("Back Underflow");
    }

    Type temp = data[backAddress];

    //reset backAddress pointer to the next in line  
    if (backAddress == frontAddress){    //only one object in queue
        frontAddress = -1;
        backAddress = -1;
        sizeOfQueue = 0;
    }
    else {
        if (backAddress == 0){           //backAddress must be wrapped around for circularity
            backAddress = capacity-1;
            sizeOfQueue--;
        }
        else {                           //backAddress is at the end or anywhere else
            backAddress--;
            sizeOfQueue--;
        }
    }

    return temp;                         //return the object that was at the backAddress
}
