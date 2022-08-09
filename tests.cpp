#define CATCH_CONFIG_MAIN
#include "ArrayQueue.h"
#include "catch.hpp"

TEST_CASE("explicit-value constructor") {
    REQUIRE_THROWS_AS(new ArrayQueue(0), QueueException);
    ArrayQueue q2(3);
    REQUIRE(q2.isEmpty());
    REQUIRE(!q2.isFull());
    REQUIRE(q2.myCapacity == 3);
}

TEST_CASE("copy constructor") {
    SECTION("empty") {
        ArrayQueue q1(4);
        ArrayQueue q2(q1);
        REQUIRE(q2.isEmpty());
        REQUIRE(!q2.isFull());
        REQUIRE(q2.myCapacity == q1.myCapacity);
        REQUIRE(q2.myFirstIndex == q1.myFirstIndex);
        REQUIRE(q2.myLastIndex == q1.myLastIndex);
        REQUIRE(q2.myArrayPtr != q1.myArrayPtr);
    }
    SECTION("1 item") {
        ArrayQueue q3(4);
        q3.append(11);
        ArrayQueue q4(q3);
        REQUIRE(!q4.isFull());
        REQUIRE(!q4.isEmpty());
        REQUIRE(q4.myCapacity == q3.myCapacity);
        REQUIRE(q4.myFirstIndex == q3.myFirstIndex);
        REQUIRE(q4.myLastIndex == q3.myLastIndex);
        REQUIRE(q4.myArrayPtr != q3.myArrayPtr);
        REQUIRE(q4.getFirst() == 11);
        REQUIRE(q4.getLast() == 11);
        REQUIRE(q4.myArrayPtr != q3.myArrayPtr);
    }
    SECTION("full") {
        // full queue
        ArrayQueue q3(4);
        q3.append(11);
        q3.append(22);
        q3.append(33);
        q3.append(44);
        ArrayQueue q5(q3);
        REQUIRE(q5.isFull());
        REQUIRE(!q5.isEmpty());
        REQUIRE(q5.myCapacity == q3.myCapacity);
        REQUIRE(q5.myFirstIndex == q3.myFirstIndex);
        REQUIRE(q5.myLastIndex == q3.myLastIndex);
        REQUIRE(q5.myArrayPtr != q3.myArrayPtr);
        REQUIRE(q5.getFirst() == 11);
        REQUIRE(q5.getLast() == 44);
        REQUIRE(q5.myArrayPtr != q3.myArrayPtr);
    }
}
TEST_CASE("append") {
    SECTION("empty") {
        ArrayQueue q1(4);
        REQUIRE(q1.isEmpty());
        REQUIRE(!q1.isFull());
        REQUIRE_THROWS_AS(q1.getFirst(), EmptyQueueException);
        REQUIRE_THROWS_AS(q1.getLast(), EmptyQueueException);
        q1.append(11);
        REQUIRE(!q1.isEmpty());
        REQUIRE(!q1.isFull());
        REQUIRE(q1.getFirst() == 11);
        REQUIRE(q1.getLast() == 11);
    }
    SECTION("1 item") {
        ArrayQueue q1(4);
        q1.append(22);
        REQUIRE(!q1.isEmpty());
        REQUIRE(!q1.isFull());
        REQUIRE(q1.getFirst() == 11);
        REQUIRE(q1.getLast() == 22);
    }
    SECTION("2 items") {
        ArrayQueue q1(4);
        q1.append(22);
        q1.append(33);
        REQUIRE(!q1.isEmpty());
        REQUIRE(!q1.isFull());
        REQUIRE(q1.getFirst() == 11);
        REQUIRE(q1.getLast() == 33);
    }
    SECTION("3 items") {
        ArrayQueue q1(4);
        q1.append(22);
        q1.append(33);
        q1.append(44);
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.isFull());
        REQUIRE(q1.getFirst() == 11);
        REQUIRE(q1.getLast() == 44);
    }
    SECTION("full queue") {
        REQUIRE_THROWS_AS(q1.append(55), FullQueueException);
    }
}

TEST_CASE("assignment") {
    SECTION("empty, smaller-to-bigger") {
        ArrayQueue q1(4);
        ArrayQueue q2(3);
        q1 = q2;
        REQUIRE(q1.isEmpty());
        REQUIRE(q1.myCapacity == 3);
        REQUIRE(q1.getSize() == 0);
        REQUIRE(q1.myFirstIndex == q2.myFirstIndex);
        REQUIRE(q1.myLastIndex == q2.myLastIndex);
        REQUIRE(q1.myArrayPtr != q2.myArrayPtr);
    }
    SECTION("empty, bigger to smaller") {
        ArrayQueue q3(3);
        ArrayQueue q4(4);
        q3 = q4;
        REQUIRE(q3.isEmpty());
        REQUIRE(q3.myCapacity == 4);
        REQUIRE(q3.getSize() == 0);
        REQUIRE(q3.myFirstIndex == q4.myFirstIndex);
        REQUIRE(q3.myLastIndex == q4.myLastIndex);
        REQUIRE(q3.myArrayPtr != q4.myArrayPtr);
    }
    SECTION("full, same-sized") {
        ArrayQueue q5(4);
        q5.append(11);
        q5.append(22);
        q5.append(33);
        q5.append(44);
        ArrayQueue q6(4);
        q6 = q5;
        REQUIRE(q6.isFull());
        REQUIRE(!q6.isEmpty());
        REQUIRE(q6.myCapacity == 4);
        REQUIRE(q6.getSize() == 4);
        REQUIRE(q6.myFirstIndex == q5.myFirstIndex);
        REQUIRE(q6.myLastIndex == q5.myLastIndex);
        for (unsigned i = 0; i < q6.myCapacity; ++i) {
            REQUIRE(q6.myArrayPtr[i] == q5.myArrayPtr[i]);
        }
        REQUIRE(q6.myArrayPtr != q5.myArrayPtr);
    }
    SECTION("full, smaller-to-larger") {
        ArrayQueue q7(3);
        ArrayQueue q5(4);
        q5.append(11);
        q5.append(22);
        q5.append(33);
        q5.append(44);
        q7 = q5;
        REQUIRE(q7.isFull());
        REQUIRE(!q7.isEmpty());
        REQUIRE(q7.myCapacity == 4);
        REQUIRE(q7.getSize() == 4);
        REQUIRE(q7.myFirstIndex == q5.myFirstIndex);
        REQUIRE(q7.myLastIndex == q5.myLastIndex);
        for (unsigned i = 0; i < q7.myCapacity; ++i) {
            REQUIRE(q7.myArrayPtr[i] == q5.myArrayPtr[i]);
        }
        REQUIRE(q7.myArrayPtr != q5.myArrayPtr);
    }
    SECTION("full, larger-to-smaller") {
        ArrayQueue q8(5);
        ArrayQueue q5(4);
        q5.append(11);
        q5.append(22);
        q5.append(33);
        q5.append(44);
        q8 = q5;
        REQUIRE(q8.isFull());
        REQUIRE(!q8.isEmpty());
        REQUIRE(q8.myCapacity == 4);
        REQUIRE(q8.getSize() == 4);
        REQUIRE(q8.myFirstIndex == q5.myFirstIndex);
        REQUIRE(q8.myLastIndex == q5.myLastIndex);
        for (unsigned i = 0; i < q8.myCapacity; ++i) {
            REQUIRE(q8.myArrayPtr[i] == q5.myArrayPtr[i]);
        }
        REQUIRE(q8.myArrayPtr != q5.myArrayPtr);
    }
    SECTION("self assignment") {
        ArrayQueue q5(4);
        q5.append(11);
        q5.append(22);
        q5.append(33);
        q5.append(44);
        q5 = q5;
        REQUIRE(q5.isFull());
        REQUIRE(!q5.isEmpty());
        REQUIRE(q5.myCapacity == 4);
        REQUIRE(q5.getSize() == 4);
        REQUIRE(q5.myArrayPtr[0] == 11);
        REQUIRE(q5.myArrayPtr[1] == 22);
        REQUIRE(q5.myArrayPtr[2] == 33);
        REQUIRE(q5.myArrayPtr[3] == 44);
    }
    SECTION("chaining") {
        ArrayQueue q1(4);
        ArrayQueue q3(3);
        ArrayQueue q5(4);
        q5.append(11);
        q5.append(22);
        q5.append(33);
        q5.append(44);
        q1 = q3 = q5;
        REQUIRE(q1.isFull());
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.myCapacity == 4);
        REQUIRE(q1.getSize() == 4);
        REQUIRE(q1.myArrayPtr[0] == 11);
        REQUIRE(q1.myArrayPtr[1] == 22);
        REQUIRE(q1.myArrayPtr[2] == 33);
        REQUIRE(q1.myArrayPtr[3] == 44);
        REQUIRE(q1.myArrayPtr != q3.myArrayPtr);
        REQUIRE(q1.myArrayPtr != q5.myArrayPtr);
        REQUIRE(q3.myArrayPtr != q5.myArrayPtr);
    }
}

TEST_CASE("remove") {
    SECTION("empty queue") {
        ArrayQueue q1(4);
        REQUIRE_THROWS_AS(q1.remove(), EmptyQueueException);
    }
    SECTION("check with 1 item") {
        ArrayQueue q1(4);
        q1.append(1);
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.remove() == 1);
        REQUIRE(q1.isEmpty());
    }
    SECTION("check with 2 items") {
        ArrayQueue q1(4);
        q1.append(11);
        q1.append(22);
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.getFirst() == 11);
        REQUIRE(q1.getLast() == 22);
        REQUIRE(q1.remove() == 11);
        REQUIRE(q1.getFirst() == 22);
        REQUIRE(q1.getLast() == 22);
        REQUIRE(q1.remove() == 22);
        REQUIRE(q1.isEmpty());
    }
    SECTION("load it up") {
        ArrayQueue q1(4);
        q1.append(111);
        q1.append(222);
        q1.append(333);
        q1.append(444);
        REQUIRE(q1.isFull());
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.getFirst() == 111);
        REQUIRE(q1.getLast() == 444);
        // start removing items
        REQUIRE(q1.remove() == 111);
        REQUIRE(!q1.isFull());
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.getFirst() == 222);
        REQUIRE(q1.getLast() == 444);

        REQUIRE(q1.remove() == 222);
        REQUIRE(!q1.isFull());
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.getFirst() == 333);
        REQUIRE(q1.getLast() == 444);

        REQUIRE(q1.remove() == 333);
        REQUIRE(!q1.isFull());
        REQUIRE(!q1.isEmpty());
        REQUIRE(q1.getFirst() == 444);
        REQUIRE(q1.getLast() == 444);

        REQUIRE(q1.remove() == 444);
        REQUIRE(!q1.isFull());
        REQUIRE(q1.isEmpty());
        REQUIRE_THROWS_AS(q1.remove(), EmptyQueueException);
    }
    SECTION("really big!") {
        ArrayQueue q2(5000);
        for (int i = 5000; i > 0; i--) {
            q2.append(i);
        }
        REQUIRE(q2.isFull());
        for (int i = 5000; i > 0; i--) {
            REQUIRE(q2.remove() == i);
        }
        REQUIRE(q2.isEmpty());
    }
}

// TEST_CASE("setCapacity") {
//     SECTION("empty queue") {
//         ArrayQueue<int> q1(1);
//         REQUIRE(q1.getCapacity() == 1);
//         REQUIRE(q1.getSize() == 0);
//         REQUIRE(q1.isEmpty());
//         REQUIRE(!q1.isFull());
//     }

// 	SECTION("increase the capacity") {
//         ArrayQueue<int> q1(1);
//         q1.setCapacity(10);
//         REQUIRE(q1.getCapacity() == 10);
//         REQUIRE(q1.getSize() == 0);
//         REQUIRE(q1.isEmpty());
//         REQUIRE(!q1.isFull());
//     }
// 	SECTION("decrease the capacity") {
//         ArrayQueue<int> q1(10);
//         q1.setCapacity(5);
//         REQUIRE(q1.getCapacity() == 5);
//         REQUIRE(q1.getSize() == 0);
//         REQUIRE(q1.isEmpty());
//         REQUIRE(!q1.isFull());
//     }
//     SECTION("set the capacity to zero") {
//         REQUIRE_THROWS_AS(q1.setCapacity(0), QueueException);
// 		// check to make sure nothing was changed
// 		REQUIRE(q1.getCapacity() == 5);
// 		REQUIRE(q1.getSize() == 0);
// 		REQUIRE(q1.isEmpty());
// 		REQUIRE(!q1.isFull());
// 	}

//     SECTION("changing capacity on a queue with items that start at the beginning of the array") {
//         ArrayQueue<int> q2(5);
//         for (int i = 0; i < 5; i++){
//             q2.append(i + 1);
//         }
//         REQUIRE(q2.getCapacity() == 5);
//         REQUIRE(q2.getSize() == 5);
//         REQUIRE(!q2.isEmpty());
//         REQUIRE(q2.isFull());
//         REQUIRE(q2.getFirst() == 1);
//         REQUIRE(q2.getLast() == 5);

//         //increase the capacity
//         q2.setCapacity(10);
//         REQUIRE(q2.getCapacity() == 10);
//         REQUIRE(q2.getSize() == 5);
//         REQUIRE(!q2.isEmpty());
//         REQUIRE(!q2.isFull());
//         REQUIRE(q2.getFirst() == 1);
//         REQUIRE(q2.getLast() == 5);
//         cout << " 2a" << flush;

//         //check to make sure appending still works
//         q2.append(6);
//         REQUIRE(q2.getLast() == 6);
//         q2.append(7);
//         q2.append(8);
//         q2.append(9);
//         q2.append(10);
//         REQUIRE(q2.getCapacity() == 10);
//         REQUIRE(q2.getSize() == 10);
//         REQUIRE(!q2.isEmpty());
//         REQUIRE(q2.isFull());
//         REQUIRE(q2.getFirst() == 1);
//         REQUIRE(q2.getLast() == 10);

//         //check to make sure that removing still works
//         REQUIRE(q2.remove() == 1);
//         REQUIRE(q2.remove() == 2);
//         REQUIRE(q2.remove() == 3);
//         REQUIRE(q2.remove() == 4);
//         REQUIRE(q2.remove() == 5);
//         REQUIRE(q2.remove() == 6);
//         REQUIRE(q2.remove() == 7);
//         REQUIRE(q2.remove() == 8);
//         REQUIRE(q2.remove() == 9);
//         REQUIRE(q2.remove() == 10);
//         REQUIRE(q2.getCapacity() == 10);
//         REQUIRE(q2.getSize() == 0);
//         REQUIRE(q2.isEmpty());
//         REQUIRE(!q2.isFull());

//         // set up a clean queue before continuing...
//         ArrayQueue<int> q3(20);
//         for (int i = 0; i < 5; i++){
//             q3.append(i + 1);
//         }
//         REQUIRE(q3.getCapacity() == 20);
//         REQUIRE(q3.getSize() == 5);
//         REQUIRE(!q3.isEmpty());
//         REQUIRE(!q3.isFull());
//         REQUIRE(q3.getFirst() == 1);
//         REQUIRE(q3.getLast() == 5);

//         //decrease the capacity
//         q3.setCapacity(10);
//         REQUIRE(q3.getCapacity() == 10);
//         REQUIRE(q3.getSize() == 5);
//         REQUIRE(!q3.isEmpty());
//         REQUIRE(!q3.isFull());
//         REQUIRE(q3.getFirst() == 1);
//         REQUIRE(q3.getLast() == 5);

//         //check to make sure appending still works
//         q3.append(6);
//         REQUIRE(q3.getLast() == 6);
//         q3.append(7);
//         q3.append(8);
//         q3.append(9);
//         q3.append(10);
//         REQUIRE(q3.getCapacity() == 10);
//         REQUIRE(q3.getSize() == 10);
//         REQUIRE(!q3.isEmpty());
//         REQUIRE(q3.isFull());
//         REQUIRE(q3.getFirst() == 1);
//         REQUIRE(q3.getLast() == 10);

//         //check to make sure that removing still works
//         REQUIRE(q3.remove() == 1);
//         REQUIRE(q3.remove() == 2);
//         REQUIRE(q3.remove() == 3);
//         REQUIRE(q3.remove() == 4);
//         REQUIRE(q3.remove() == 5);
//         REQUIRE(q3.remove() == 6);
//         REQUIRE(q3.remove() == 7);
//         REQUIRE(q3.remove() == 8);
//         REQUIRE(q3.remove() == 9);
//         REQUIRE(q3.remove() == 10);
//         REQUIRE(q3.getCapacity() == 10);
//         REQUIRE(q3.getSize() == 0);
//         REQUIRE(q3.isEmpty());
//         REQUIRE(!q3.isFull());
//     }

// 	SECTION("setCapacity() on a queue that has items starting in the middle of the array, not wrapping around") {
//         ArrayQueue<int> q4(5);
//         for (int i = 0; i < 5; i++){
//             q4.append(i + 1);
//         }
//         q4.remove();
//         q4.remove();
//         REQUIRE(q4.getCapacity() == 5);
//         REQUIRE(q4.getSize() == 3);
//         REQUIRE(!q4.isEmpty());
//         REQUIRE(!q4.isFull());
//         REQUIRE(q4.getFirst() == 3);
//         REQUIRE(q4.getLast() == 5);

//         // increase the capacity
//         q4.setCapacity(10);
//         REQUIRE(q4.getCapacity() == 10);
//         REQUIRE(q4.getSize() == 3);
//         REQUIRE(!q4.isEmpty());
//         REQUIRE(!q4.isFull());
//         REQUIRE(q4.getFirst() == 3);
//         REQUIRE(q4.getLast() == 5);

//         // check to make sure appending still works
//         q4.append(6);
//         q4.append(7);
//         q4.append(8);
//         q4.append(9);
//         q4.append(10);
//         q4.append(11);
//         q4.append(12);
//         REQUIRE(q4.getCapacity() == 10);
//         REQUIRE(q4.getSize() == 10);
//         REQUIRE(!q4.isEmpty());
//         REQUIRE(q4.isFull());
//         REQUIRE(q4.getFirst() == 3);
//         REQUIRE(q4.getLast() == 12);

//         // check to make sure removing still works
//         REQUIRE(q4.remove() == 3);
//         REQUIRE(q4.remove() == 4);
//         REQUIRE(q4.remove() == 5);
//         REQUIRE(q4.remove() == 6);
//         REQUIRE(q4.remove() == 7);
//         REQUIRE(q4.remove() == 8);
//         REQUIRE(q4.remove() == 9);
//         REQUIRE(q4.remove() == 10);
//         REQUIRE(q4.remove() == 11);
//         REQUIRE(q4.remove() == 12);
//         REQUIRE(q4.getCapacity() == 10);
//         REQUIRE(q4.getSize() == 0);
//         REQUIRE(q4.isEmpty());
//         REQUIRE(!q4.isFull());

//         // create a clean queue before continuing...
//         ArrayQueue<int> q5(10);
//         for (int i = 0; i < 10; i++){
//             q5.append(i + 1);
//         }
//         for (int i = 0; i < 7; i++){
//             q5.remove();
//         }
//         REQUIRE(q5.getCapacity() == 10);
//         REQUIRE(q5.getSize() == 3);
//         REQUIRE(!q5.isEmpty());
//         REQUIRE(!q5.isFull());
//         REQUIRE(q5.getFirst() == 8);
//         REQUIRE(q5.getLast() == 10);

//         // reduce the capacity
//         q5.setCapacity(5);
//         REQUIRE(q5.getCapacity() == 5);
//         REQUIRE(q5.getSize() == 3);
//         REQUIRE(!q5.isEmpty());
//         REQUIRE(!q5.isFull());
//         REQUIRE(q5.getFirst() == 8);
//         REQUIRE(q5.getLast() == 10);

//         // check to make sure appending still works
//         q5.append(11);
//         q5.append(12);
//         REQUIRE(q5.getCapacity() == 5);
//         REQUIRE(q5.getSize() == 5);
//         REQUIRE(!q5.isEmpty());
//         REQUIRE(q5.isFull());
//         REQUIRE(q5.getFirst() == 8);
//         REQUIRE(q5.getLast() == 12);

//         // check to make sure removing still works
//         REQUIRE(q5.remove() == 8);
//         REQUIRE(q5.remove() == 9);
//         REQUIRE(q5.remove() == 10);
//         REQUIRE(q5.remove() == 11);
//         REQUIRE(q5.remove() == 12);
//         REQUIRE(q5.getCapacity() == 5);
//         REQUIRE(q5.getSize() == 0);
//         REQUIRE(q5.isEmpty());
//         REQUIRE(!q5.isFull());
//     }

// 	SECTION("setCapacity() on a queue with values that wrap around the array") {
//         ArrayQueue<int> q6(5);
//         for (int i = 0; i < 5; i++){
//             q6.append(i + 1);
//         }
//         q6.remove();
//         q6.remove();
//         q6.remove();
//         q6.append(6);
//         q6.append(7);
//         REQUIRE(q6.getCapacity() == 5);
//         REQUIRE(q6.getSize() == 4);
//         REQUIRE(!q6.isEmpty());
//         REQUIRE(!q6.isFull());
//         REQUIRE(q6.getFirst() == 4);
//         REQUIRE(q6.getLast() == 7);

//         // increase the capacity
//         q6.setCapacity(10);
//         REQUIRE(q6.getCapacity() == 10);
//         REQUIRE(q6.getSize() == 4);
//         REQUIRE(!q6.isEmpty());
//         REQUIRE(!q6.isFull());
//         REQUIRE(q6.getFirst() == 4);
//         REQUIRE(q6.getLast() == 7);

//         // check to make sure appending still works
//         q6.append(8);
//         q6.append(9);
//         q6.append(10);
//         q6.append(11);
//         q6.append(12);
//         q6.append(13);
//         REQUIRE(q6.getCapacity() == 10);
//         REQUIRE(q6.getSize() == 10);
//         REQUIRE(!q6.isEmpty());
//         REQUIRE(q6.isFull());
//         REQUIRE(q6.getFirst() == 4);
//         REQUIRE(q6.getLast() == 13);

//         // check to make sure removing still works
//         REQUIRE(q6.remove() == 4);
//         REQUIRE(q6.remove() == 5);
//         REQUIRE(q6.remove() == 6);
//         REQUIRE(q6.remove() == 7);
//         REQUIRE(q6.remove() == 8);
//         REQUIRE(q6.remove() == 9);
//         REQUIRE(q6.remove() == 10);
//         REQUIRE(q6.remove() == 11);
//         REQUIRE(q6.remove() == 12);
//         REQUIRE(q6.remove() == 13);
//         REQUIRE(q6.getCapacity() == 10);
//         REQUIRE(q6.getSize() == 0);
//         REQUIRE(q6.isEmpty());
//         REQUIRE(!q6.isFull());

//         // set up a clean queue before continuing...
//         ArrayQueue<int> q7(10);
//         for(int i = 0; i < 10; i++){
//             q7.append(i + 1);
//         }
//         for(int i = 0; i < 8; i++){
//             q7.remove();
//         }
//         q7.append(11);
//         q7.append(12);
//         REQUIRE(q7.getCapacity() == 10);
//         REQUIRE(q7.getSize() == 4);
//         REQUIRE(!q7.isEmpty());
//         REQUIRE(!q7.isFull());
//         REQUIRE(q7.getFirst() == 9);
//         REQUIRE(q7.getLast() == 12);

//         // reduce the capacity
//         q7.setCapacity(6);
//         REQUIRE(q7.getCapacity() == 6);
//         REQUIRE(q7.getSize() == 4);
//         REQUIRE(!q7.isEmpty());
//         REQUIRE(!q7.isFull());
//         REQUIRE(q7.getFirst() == 9);
//         REQUIRE(q7.getLast() == 12);

//         // check to make sure appending still works
//         q7.append(13);
//         q7.append(14);
//         REQUIRE(q7.getCapacity() == 6);
//         REQUIRE(q7.getSize() == 6);
//         REQUIRE(!q7.isEmpty());
//         REQUIRE(q7.isFull());
//         REQUIRE(q7.getFirst() == 9);
//         REQUIRE(q7.getLast() == 14);

//         // check to make sure removing still works
//         REQUIRE(q7.remove() == 9);
//         REQUIRE(q7.remove() == 10);
//         REQUIRE(q7.remove() == 11);
//         REQUIRE(q7.remove() == 12);
//         REQUIRE(q7.remove() == 13);
//         REQUIRE(q7.remove() == 14);
//         REQUIRE(q7.getCapacity() == 6);
//         REQUIRE(q7.getSize() == 0);
//         REQUIRE(q7.isEmpty());
//         REQUIRE(!q7.isFull());
//     }

// 	SECTION("reducing capacity to less than the current size") {
//         ArrayQueue<int> q8(10);
//         for(int i = 0; i < 8; i++){
//             q8.append(i + 1);
//         }
//         REQUIRE(q8.getCapacity() == 10);
//         REQUIRE(q8.getSize() == 8);
//         REQUIRE(!q8.isEmpty());
//         REQUIRE(!q8.isFull());
//         REQUIRE(q8.getFirst() == 1);
//         REQUIRE(q8.getLast() == 8);

//         REQUIRE_THROWS_AS(q8.setCapacity(5), QueueException);
//         // check to make sure nothing changed
//         REQUIRE(q8.getCapacity() == 10);
//         REQUIRE(q8.getSize() == 8);
//         REQUIRE(!q8.isEmpty());
//         REQUIRE(!q8.isFull());
//         REQUIRE(q8.getFirst() == 1);
//         REQUIRE(q8.getLast() == 8);
//         REQUIRE(q8.remove() == 1);
//         REQUIRE(q8.remove() == 2);
//         REQUIRE(q8.remove() == 3);
//         REQUIRE(q8.remove() == 4);
//         REQUIRE(q8.remove() == 5);
//         REQUIRE(q8.remove() == 6);
//         REQUIRE(q8.remove() == 7);
//         REQUIRE(q8.remove() == 8);
// 	}

// 	SECTION("copy a full queue, where myFirst and myLast are not zero, so newer items precede older items in the queue") {
//         ArrayQueue<int> q9(3);
//         q9.append(11);
//         q9.append(12);
//         q9.append(13);
//         REQUIRE(q9.remove() == 11);
//         q9.append(14);
//         REQUIRE(q9.remove() == 12);
//         q9.append(15);
//         q9.setCapacity(4);
//         REQUIRE(q9.getCapacity() == 4);
//         REQUIRE(q9.getFirst() == 13);
//         REQUIRE(q9.getLast() == 15);
//         REQUIRE(q9.remove() == 13);
//         REQUIRE(q9.getFirst() == 14);
//         REQUIRE(q9.getLast() == 15);
//         REQUIRE(q9.remove() == 14);
//         REQUIRE(q9.getFirst() == 15);
//         REQUIRE(q9.getLast() == 15);
//         REQUIRE(q9.remove() == 15);
//     }
// }
