#ifndef _LinkList_H
#define _LinkList_H

#include"MyList.h"

typedef struct LinkNode *Link;
struct LinkNode{										// the link list struct
	int data;
	Link next;
};

class LinkList : public MyList{							// the list class using link list
public :
	LinkList();											// the constructor
	virtual ~LinkList();								// the destructor

	virtual const int& operator [](const int) const;	// get the element at the position
	virtual void attach(const int);						// attach the value at end
	virtual void insert(const int, const int);			// insert the value before the position
	virtual void del(const int);						// delete the position
	void prtAll();										// print out all the information in the list

protected :
	Link head, tail;									// the head and tail pointer of the list
};

#endif //_LinkList_H