/* Stack.h provides a (dynamic-array-based) Stack class.
 * Joel Adams, for CS 112 at Calvin College.
 * Student Name: Lorrayya Williams
 * Date: November 3, 2018
 * 
 * Invariant: mySize == 0 && isEmpty() && !isFull()
 *         || mySize == myCapacity && !isEmpty() && isFull()
 *         || mySize > 0 && mySize < myCapacity && !isEmpty() && !isFull().
 * Notes: 
 * 1. Member mySize always contains the index of the next empty space in myArray
 *        (the index of the array element into which the next pushed item will be placed).
 * 2. Sending push() to a full Stack throws the exception Stack<Item>::Overflow.
 * 3. Sending pop() or peekTop() to an empty Stack throws the exception Stack<Item>::Underflow.
 */

#ifndef STACK_H_
#define STACK_H_

#include "StackException.h"
#include <string>
#include <iostream>
using namespace std;

template <class Item>

class Stack {
public:
	Stack(unsigned capacity);
	Stack(const Stack& original);
	~Stack();
	Stack& operator=(const Stack& original);
	bool isEmpty()const {return mySize==0;}
	void push(Item it);
	Item peekTop() const;
	bool isFull(){ return mySize==myCapacity;}
	Item& pop();
	unsigned getSize();
	unsigned getCapacity();
	void setCapacity(unsigned capacity);
protected:
	void makeCopyOf(const Stack& original);
	
private:
	unsigned myCapacity;
	unsigned mySize;
	Item*    myArray;
	friend class StackTester;
};

template <class Item>
Stack<Item>::Stack(unsigned capacity) {
	if (capacity == 0){
		throw StackException("Stack(capacity)" , "Capacity must be postive!");
	}
	else{
		mySize = 0;
		myCapacity = capacity;
		myArray = new Item[capacity];
	}
}

/* copy constructor
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original.
 */
template <class Item>
Stack<Item>::Stack(const Stack& original) {
	makeCopyOf(original);
}

/* utility method containing code refactored from
 *  the copy constructor and operator=.
 * Parameter: original, a Stack (const reference).
 * Precondition: original.myCapacity > 0.
 * Postcondition: I am a copy of original.
 */
template <class Item>
void Stack<Item>::makeCopyOf(const Stack& original) {
	myCapacity = original.myCapacity;
	myArray = new Item[myCapacity];

	for (unsigned i = 0; i < myCapacity; i++) {
		myArray[i] = original.myArray[i];
	}
	mySize = original.mySize;
}

/* destructor
 * Postcondition: myCapacity == 0 && mySize == 0
 *             && myArray has been deallocated.
 */
template <class Item>
Stack<Item>::~Stack() {
	delete[] myArray;
	myArray = NULL;
	myCapacity = 0;
	mySize = 0;
}

/* assignment operator
 * Parameter: original, a Stack (const reference).
 * Postcondition: I am a copy of original
 *              && I have been returned.
 */
template <class Item>
Stack<Item>& Stack<Item>::operator=(const Stack& original) {
	if (this != &original) {
		delete[] myArray;
		makeCopyOf(original);
	}
	return *this;
}

//Returns item on the top of the stack
template <class Item>
Item Stack<Item>::peekTop() const {
	if (isEmpty()) {
		throw StackException("peekTop()",  "The stack is empty!");
	}
	return myArray[mySize - 1];
}

//Adds item to the top of the stack
template <class Item>
void Stack<Item>::push(Item item) {
	if ( isFull()){
		throw StackException("push(item)", "The stack is full!");
	}
	else{
	myArray[mySize] = item;
	mySize += 1;
	}
}

//Removes and returns the top item from the stack
template <class Item>
Item& Stack<Item>::pop() {
	if (mySize == 0) {
		throw StackException("pop()", "The Stack is empty!");
	} else {
		Item thing;
		mySize -= 1;
		return myArray[mySize];
	}

}

template <class Item>
unsigned Stack<Item>::getSize(){
	return mySize;
}

template <class Item>
unsigned Stack<Item>::getCapacity(){
	return myCapacity;
}

template <class Item>
void Stack<Item>::setCapacity(unsigned capacity){

	if (capacity < mySize){
		throw StackException("setCapacity(capacity) ", "The new capacity is smaller than the size");
	}

//	if( myCapacity > capacity ){
//		throw StackException("setCapacity(capacity) ", "The old capacity is larger than new capacity");
//	}
	if(capacity == 0){
		throw StackException("setCapacity(capacity) ", "The new capacity must be larger than 0");
	}
//	if(myCapacity == capacity){
//
//	}
	else {
		if(myCapacity != capacity){
			Item *newarray = new Item[capacity];

			for (unsigned i = 0; i < mySize; i++) {
				newarray[i] = myArray[i];

			}
			delete [] myArray;
			myArray = newarray;
			myCapacity = capacity;
		}
	}
}




#endif

