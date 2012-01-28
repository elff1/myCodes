#ifndef _ArrList_H
#define _ArrList_H

#include"MyList.h"

class ArrList : public MyList{									// the list class using array
public :
	ArrList(int cap = 0){Capacity = cap; Arr = new int[cap];}	// the constructor
	//ArrList(cap):MyList(0), Arr(0), Capacity(cap){Arr = new int[cap];}
	virtual ~ArrList(){delete []Arr;}							// the destructor

	virtual const int& operator [](const int) const;			// get the element at the position
	virtual void attach(const int);								// attach the value at end
	virtual void insert(const int, const int);					// insert the value before the position
	virtual void del(const int);								// delete the position
	const int getCap(){return Capacity;}						// get the capacity of the array list
	void prtAll();												// print out all the information in the list

protected :
	int *Arr;													// the pointer of the array
	int Capacity;												// the capacity of the list

private :
	void ensureMinCap(const int);								// ensure the minimum capacity
};

#endif //_ArrList_H