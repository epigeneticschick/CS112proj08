/*Detectsa palindrome
 * palindromedetector.cpp
 * Lorrayya Williams
 *  Created on: Nov 19, 2018 for CS 112
 *      Author: llw5
 */

#include "palindromedetector.h"

using namespace std;


palindromedetector::palindromedetector(string input, string output){
	//intializes input file
	inputName = input;

	//intializes output file
	outputName = output;

}

//Tests if the line is a palindrome and returns a boolean.
bool palindromedetector::isPalindrome(string line){

	Stack <char> s(1); //intializes a Stack
	ArrayQueue<char> q(1); //intializes an Array Queue
	if(line == ""){
		return false;
	}

	for(unsigned i =0; i< line.size(); ++i){
		//converts characters to lowercase
		char c = line[i];
		c = tolower(c);

		if(isalpha(line[i])){
		//pushes it onto a stack
		try {
			s.push(c);

		}
		catch(const StackException& se) {
			s.setCapacity(s.getCapacity() *2);
			s.push(c);
		}


		//Appends to a queue
		try{
			q.append(c);
		}
		catch(const FullQueueException& fqe){
			q.setCapacity(s.getCapacity()*2);
			q.append(c);
		}
		}
	}

	for(unsigned i = 0; i < s.getSize(); i++){
		if(s.pop()!= q.remove()){
		while(!s.isEmpty()){
			q.remove();
			s.pop();
		}
		return false;
		}
	}
		return true;
}

//Detects palindromes in a file and outputs files with palindromes marked
void palindromedetector::detectPalindromes(){
	 //opens input file
	ifstream fin(inputName.c_str());
	assert(fin.is_open());

	 //creates and opens output file
	ofstream fout(outputName.c_str());
	assert(fout.is_open());

	string line;
	while(!fin.eof()){
		getline(fin, line);
		if(isPalindrome(line)){
			fout << line << " *** " << endl;
		}
		else{
			fout << line << endl;
		}
	}

	fin.close();
	fout.close();
}
