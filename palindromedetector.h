/*Detects a palindrome.
 * palindromedector.h
 * Lorrayya Williams
 *  Created on: Nov 19, 2018 for CS 112
 *      Author: llw5
 */

#ifndef PALINDROMEDETECTOR_H_
#define PALINDROMEDETECTOR_H_
#include "ArrayQueue.h"
#include "Stack.h"
#include "StackException.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <stdio.h>

using namespace std;

class palindromedetector {
public:
	palindromedetector(string input, string output);
	bool isPalindrome(string line);
	void detectPalindromes();

private:
	string inputName;
	string outputName;


};



#endif /* PALINDROMEDECTOR_H_ */
