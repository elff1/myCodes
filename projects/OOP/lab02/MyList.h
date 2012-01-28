#ifndef _MyList_H
#define _MyList_H

class MyList{												// the base class of the list
public :
	MyList(){n = 0;}										// the constructor
	~MyList(){}												// the destructor
	virtual const int& operator [](const int) const{return 0;}	// visit a position unchanged
	virtual void attach(const int){}						// attach the value at end
	virtual void insert(const int, const int){}				// insert the value before the position
	virtual void del(const int){}							// delete the position
	const int& getn(){return n;}

protected :
	int n;													// the number of the elements
};

#endif //_MyList_H