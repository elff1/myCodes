#include <iostream>
#include <fstream>
#include <string>
#include "MyString.h"

// define the maximum number of different strings in a[].
#define MaxN 100

using namespace std;

int main(void){
	/*
	* fname is the name of the data file,
	* substr is the sub-string that search for,
	* str is the current input string.
	*/
	MyString fname, substr, str;
	// a[] stores the strings containing the sub-string.
	MyString a[MaxN];
	int i, j, n;	// n is the number of the strings in a[].

	// input the data file name.
	cout << "The data file name: ";
	cin >> fname;
	// open the file and connect it to a stream named infile.
	ifstream infile(fname.CStyle());
	if(!infile){
		cerr << "error: unable to open input file: " << fname << endl;
		return -1;
	}
	// input the sub-string.
	cout << "The substring: ";
	cin >> substr;

	// initialize the number of strings in a[].
	n = 0;
	// scan each word in the data file until there is no more words.
	while(infile >> str, str.size()){
		// if the word contains the sub-string, add it to a[].
		if(str.find(substr, 0) < str.size()){
			// find a correct position for the word in a[].
			for(i = 0; i < n; i++)
				if(a[i].compare(str) > 0)
					break;
			// if the word isn't in a[], add it to a[].
			if(!i || a[i-1].compare(str) < 0){
				for(j = n; j > i; j--)
					a[j] = a[j-1];
				a[j] = str;
				n++;
			}
		}
	}
	// print out all the strings containing the sub-string.
	for(i = 0; i < n; i++)
		cout << a[i] << endl;

	// close the data file.
	infile.close();
}