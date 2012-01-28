// Queue.h: interface for the Queue class,
//			the defination of exception classes.
//
//////////////////////////////////////////////////////////////////////

#ifndef _Queue_H
#define _Queue_H

#include "ListItem.h"

// the base exception class.
class qError{
protected:
	// the exception information
	char *info;

public:
	// the construction
	qError(){info = NULL;}
	// the exception information query
	char *what(){return info;}
};

// the alloc failed exception class
class AllocFail : public qError{
public:
	// the constructor
	AllocFail(){info = "Alloc new space failed.";}
};

// the dequeue from an empty queue exception class
class OutEmpty : public qError{
public:
	// the constructor
	OutEmpty(){info = "Dequeue from an empty queue.";}
};

// the queue class
template <class Type>
class Queue{
public:
	Queue();
	~Queue();

	// the enqueue function
	bool inQueue(const Type &);
	// the dequeue function
	bool outQueue(Type &);
	// the empty query function
	bool isEmpty(){return (n == 0);}
	// the size query function
	int size(){return n;}
	// the data printer function
	void printOut();
private:
	// the size of the queue
	int n;
	// the head and tail pointer of the queue
	ListItem<Type> *head, *tail;
};

#endif // _Queue_H
