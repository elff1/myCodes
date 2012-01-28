// Integer.h: interface for the Integer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _Integer_H
#define _Integer_H

#include<iostream>
using namespace std;

class Integer{
public:
	// the constructor
	Integer(int data = 0):d(data){}

private:
	int d;

// the output operator function.
friend ostream& operator << (ostream& os, const Integer& x){
	os << x.d;
	return os;
}
};

#endif // _Integer_H