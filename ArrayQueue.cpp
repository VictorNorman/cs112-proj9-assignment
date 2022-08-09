/* ArrayQueue.cpp defines the methods for class ArrayQueue.
 * Joel Adams, for CS 112 at Calvin University.
 */

#include "ArrayQueue.h"

#include <cstring>  // memcpy()
using namespace std;

ArrayQueue::ArrayQueue(unsigned capacity) {
    if (capacity == 0) {
        throw QueueException("ArrayQueue constructor",
                             "cannot create Queue with 0 capacity");
    }
    myCapacity = capacity;
    mySize = 0;
    myFirstIndex = 0;
    myLastIndex = myCapacity - 1;
    myArrayPtr = new Item[myCapacity]();
}

/* copy constructor
 * @param: original, the ArrayQueue to be copied.
 */
ArrayQueue::ArrayQueue(const ArrayQueue& original) { makeCopyOf(original); }

/* utility method to build copies
 * @param: original, the ArrayQueue to be copied.
 */
void ArrayQueue::makeCopyOf(const ArrayQueue& original) {
    mySize = original.mySize;
    myCapacity = original.myCapacity;
    myFirstIndex = original.myFirstIndex;
    myLastIndex = original.myLastIndex;
    myArrayPtr = new Item[myCapacity];
    memcpy(myArrayPtr, original.myArrayPtr, myCapacity * sizeof(Item));
}

ArrayQueue::~ArrayQueue() {
    delete[] myArrayPtr;
    myArrayPtr = NULL;
    mySize = myFirstIndex = myLastIndex = 0;
}

/* assignment operator
 * @param: aQueue, an ArrayQueue/
 * @return: myself.
 */
ArrayQueue& ArrayQueue::operator=(const ArrayQueue& aQueue) {
    if (this != &aQueue) {
        delete[] myArrayPtr;
        makeCopyOf(aQueue);
    }
    return *this;
}

/* Am I empty?
 * @return: true if I am empty, false othewise.
 */
bool ArrayQueue::isEmpty() const { return mySize == 0; }

/* Am I full?
 * @return: true if I am full, false othewise.
 */
bool ArrayQueue::isFull() const { return getSize() == myCapacity; }

/* accessor for myCapacity
 * @return myCapacity.
 */
unsigned ArrayQueue::getCapacity() const { return myCapacity; }

/* accessor for mySize
 * @return mySize.
 */
unsigned ArrayQueue::getSize() const { return mySize; }

Item ArrayQueue::getFirst() const {
    if (isEmpty()) {
        throw EmptyQueueException("getFirst()");
    }
    return myArrayPtr[myFirstIndex];
}

Item ArrayQueue::getLast() const {
    if (isEmpty()) {
        throw EmptyQueueException("getLast()");
    }
    return myArrayPtr[myLastIndex];
}

void ArrayQueue::append(const Item& it) {
    if (isFull()) {
        throw FullQueueException("append()");
    }
    myLastIndex = (myLastIndex + 1) % myCapacity;
    myArrayPtr[myLastIndex] = it;
    mySize++;
}

Item ArrayQueue::remove() {
    if (isEmpty()) {
        throw EmptyQueueException("remove()");
    }
    Item ret = myArrayPtr[myFirstIndex];
    myFirstIndex = (myFirstIndex + 1) % myCapacity;
    mySize--;
    return ret;
}
