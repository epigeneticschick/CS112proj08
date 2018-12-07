/* ArrayQueue.h declares a Queue class using a dynamic array.
 * Begun by: Joel Adams, for CS 112 at Calvin College.
 * Student name: Lorrayya Williams
 * Date:November 12, 2018
 * 
 * Class Invariant: 
 *    mySize == 0 ||
 *    mySize > 0 && myArray[myFirst] == getFirst()
 *               && myArray[myLast] == getLast().
 * 
 *  (When I am not empty:
 *     myFirstIndex is the index of my oldest value;
 *     myLastIndex is the index of my newest value.)
 */

#ifndef ARRAY_QUEUE_H_
#define ARRAY_QUEUE_H_

#include "QueueException.h"
#include <cstring>

template <class Item>
 
class ArrayQueue {
public:
	ArrayQueue();
	ArrayQueue(unsigned capacity);
	ArrayQueue(const ArrayQueue& original);
	virtual ~ArrayQueue();
	ArrayQueue& operator=(const ArrayQueue& original);
	unsigned getSize() const;
	unsigned getCapacity() const;
	bool isEmpty() const;
	bool isFull() const;
	unsigned getFirst();
	unsigned getLast();
	void append(const Item& it);
	Item remove();
	void setCapacity(unsigned capacity);
protected:
	virtual void makeCopyOf(const ArrayQueue& original);
private:
	unsigned mySize;       // number of items I contain
	unsigned myCapacity;   // how many items I can store
	unsigned myFirstIndex; // index of oldest item (if any)
	unsigned myLastIndex;  // index of newest item (if any)
	Item*    myArrayPtr;   // dynamic array of items

	friend class ArrayQueueTester;
};
//Default Constructor
template <class Item>
ArrayQueue<Item>::ArrayQueue(){
mySize = 0;
myCapacity =0;
myFirstIndex = 0;
myLastIndex = -1;
myArrayPtr = new Item[myCapacity];
}

//Explicit constructor
template <class Item>
ArrayQueue<Item>::ArrayQueue(unsigned capacity){

	if(capacity == 0){
		throw QueueException("ArrayQueue()", "Capacity is 0. It cannot have a 0 capacity.");
	}
	else{
		mySize = 0;
		myCapacity = capacity;
		myFirstIndex = 0;
		myLastIndex = -1;
		myArrayPtr = new Item[myCapacity];
	}

}
/* copy constructor
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
template <class Item>
ArrayQueue<Item>::ArrayQueue(const ArrayQueue& original) {
	makeCopyOf(original);
}

/* utility method to build copies
 * @param: original, the ArrayQueue to be copied.
 * Postcondition: I am a deep copy of original.
 */
template <class Item>
void ArrayQueue<Item>::makeCopyOf(const ArrayQueue& original) {
	mySize = original.mySize;
	myCapacity = original.myCapacity;
	myFirstIndex = original.myFirstIndex;
	myLastIndex = original.myLastIndex;
	myArrayPtr = new Item[myCapacity];
	memcpy(myArrayPtr, original.myArrayPtr, myCapacity*sizeof(Item) );
}

/* destructor
 * Postcondition: my dynamic array has been deallocated.
 */
template <class Item>
ArrayQueue<Item>::~ArrayQueue() {
	delete [] myArrayPtr;
	myArrayPtr = NULL;
	mySize = myFirstIndex = myLastIndex = 0;
}

/* assignment operator
 * @param: aQueue, an ArrayQueue/
 * @return: myself.
 * Postcondition: I am a deep copy of aQueue.
 */
template <class Item>
ArrayQueue<Item>& ArrayQueue<Item>::operator=(const ArrayQueue& aQueue) {
	if (this != &aQueue) {
		delete [] myArrayPtr;
		makeCopyOf(aQueue);
	}
	return *this;
}

/* Am I empty?
 * @return: true if I am empty, false othewise.
 */
template <class Item>
bool ArrayQueue<Item>::isEmpty() const {
	return mySize == 0;
}
//
///* Am I full?
// * @return: true if I am full, false othewise.
// */
template <class Item>
bool ArrayQueue<Item>::isFull() const {
	return getSize() == myCapacity;
}

/* accessor for myCapacity
 * @return myCapacity.
 */
template <class Item>
unsigned ArrayQueue<Item>::getCapacity() const {
	return myCapacity;
}

/* accessor for mySize
 * @return mySize.
 */
template <class Item>
unsigned ArrayQueue<Item>::getSize() const {
	return mySize;
}

//accessor for First
template <class Item>
unsigned ArrayQueue<Item>::getFirst(){
	if(isEmpty()){
		throw EmptyQueueException("getFirst()");
	}
	return myArrayPtr[myFirstIndex];
}

// accessor for Last Item
template <class Item>
unsigned ArrayQueue<Item>::getLast(){
	if( isEmpty()){
		throw EmptyQueueException("getLast()");
	}
	return myArrayPtr[myLastIndex];
}

//Adds item to the end of a list
template <class Item>
void ArrayQueue<Item>::append(const Item& it ){
	if(isFull()){
		throw  FullQueueException("append(it)");
	}
	myLastIndex = (myLastIndex +1) % myCapacity;
	myArrayPtr[myLastIndex] = it;
	mySize++;
}

//Removes first item
template <class Item>
Item ArrayQueue<Item>::remove(){
	if(isEmpty()){
		throw EmptyQueueException("remove()");
	}
	Item result;
	result = myArrayPtr[myFirstIndex];
	myFirstIndex = (myFirstIndex +1) % myCapacity;
	mySize--;
	return result;
	}

//Changes the Capacity of the Array
template <class Item>
void ArrayQueue<Item>::setCapacity(unsigned capacity){
	if( capacity == 0 || capacity <getSize() ){
		throw QueueException("setCapacity(capacity):", "Capacity is out of range!");
	}

	Item *newarray = new Item[capacity];
	//copies items to new array
	for (unsigned i = 0; i < getSize(); i++) {
		newarray[i] = myArrayPtr[(i + myFirstIndex) % myCapacity];
	}
	myFirstIndex = 0;
	myLastIndex = mySize -1;
	delete [] myArrayPtr;
	myArrayPtr = newarray;
	myCapacity = capacity;

}

#endif /*ARRAY_QUEUE_H_*/
