/* Tests the palindromedetector class
 * palindromedetectortester.cpp
 *	Lorrayya Williams
 *  Created on: Nov 19, 2018 for CS 112
 *      Author: llw5
 */

#include "palindromedetectortester.h"
#include <iostream>

using namespace std;


void palindromedetectortester::runTests(){
	cout << "Testing palindrome class ... " << endl;
	testispalindrome();
	testdetectpalindrome();
	cout << " All Tests Passed! " << endl;
}

void palindromedetectortester::testispalindrome(){
	cout << " Testing isPalindrome()... " << flush;
	palindromedetector p("ispalindrometester.txt", "output.txt");

	//tests palindrome
	assert(p.isPalindrome("bob")== true);
	cout << " 0 " << flush;

	//tests non-palindrome
	assert(p.isPalindrome("Lorrayya")== false);
	cout << " 1 " << flush;

	//tests empty line
	assert(p.isPalindrome("") != true);
	cout << " 2 " << flush;

	cout<< "Passed!" << endl;
}

void palindromedetectortester::testdetectpalindrome(){
	cout << " Testing testdetectpalindrome()... " << flush;
	//Tests file with all palindromes
	palindromedetector p("ispalindrometester.txt", "output.txt");
	p.detectPalindromes();
	ifstream fin("output.txt");
	assert(fin.is_open());
	string line;
	getline(fin,line);
	assert( line == "Bob *** ");

	getline(fin, line);
	assert( line == "Civic *** ");

	getline(fin, line);
	assert( line == "Anna *** ");
	fin.close();
	cout << " 0 " << flush;

	//tests file with punctuation and mixture of regular text and palindromes
	palindromedetector p1("palindrometester.txt", "output2.txt");
	p1.detectPalindromes();

	ifstream in("output2.txt");
	assert(in.is_open());
	string level;
	getline(in,level);
	assert(level == "I like Pizza" );

	getline(in, level);
	assert(level == "Never odd or even. *** ");

	getline(in,level);
	assert(level== "With truth, there is freedom");

	getline(in,level);
	assert(level == "racecar *** ");

	getline(in, level);
	assert(level == "pull up *** ");

	cout << " 1 " << flush;

	cout<< " Passed! " << endl;
}
