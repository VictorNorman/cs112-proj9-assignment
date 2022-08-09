/* ArrayQueue.h declares a Queue class using a dynamic array.
 * Begun by: Joel Adams, for CS 112 at Calvin University.
 */

#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include "QueueException.h"

typedef int Item;

class ArrayQueue {
   public:
    ArrayQueue(unsigned capacity);
    ArrayQueue(const ArrayQueue& original);
    virtual ~ArrayQueue();
    ArrayQueue& operator=(const ArrayQueue& original);
    Item getFirst() const;
    Item getLast() const;
    void append(const Item& it);
    Item remove();
    unsigned getSize() const;
    unsigned getCapacity() const;
    bool isEmpty() const;
    bool isFull() const;

   protected:
    virtual void makeCopyOf(const ArrayQueue& original);

   // NOTE: for testing purposes we'll expose the innards of
   // this class. Should be changed to private: if we were
   // to release this for general use.
   public:
    unsigned mySize;        // number of items I contain
    unsigned myCapacity;    // how many items I can store
    unsigned myFirstIndex;  // index of oldest item (if any)
    unsigned myLastIndex;   // index of newest item (if any)
    Item* myArrayPtr;       // dynamic array of items

};

#endif /*ARRAY_QUEUE_H_*/
