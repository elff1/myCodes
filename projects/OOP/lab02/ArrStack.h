#ifndef _ArrStack_H
#define _ArrStack_H

#include"ArrList.h"

class ArrStack : public ArrList{						// the stack using array list
public :
	ArrStack(int cap = 0):ArrList(cap){}				// the constructor
	~ArrStack(){}										// the destructor
	const bool IsEmpty(){return (n == 0);}				// judge whether the stack is empty
	const int &Top(){return Arr[n - 1];}				// get the top element in the stack
	void Push(const int d){attach(d);}					// push a new element into the stack
	void Pop(){del(n - 1);}								// delete the top element in the stack
	void MakeEmpty(){n = 0;}							// make the stack empty
};

#endif //_ArrStack_H