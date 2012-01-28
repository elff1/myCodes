// Queue.cpp: implementation of the Queue class.
//
//////////////////////////////////////////////////////////////////////

#include<iostream>
#include<stdexcept>
#include "Queue.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

template <class Type>
Queue<Type>::Queue(){
	n = 0;
	head = tail = NULL;
}

template <class Type>
Queue<Type>::~Queue(){
	ListItem<Type> *p, *q;

	// free the space of each node
	p = head;
	while(p){
		q = p->next;
		delete p;
		p = q;
	}
}

// the enqueue function
template <class Type>
bool Queue<Type>::inQueue(const Type &data){
	ListItem<Type> *p = NULL;

	try{
		// new a space for the data
		p = new ListItem<Type>(data);
		// if alloc failed, throw an exception class
		if(!p)
			throw AllocFail();

		// insert the new node into the queue
		if(!head){
			head = tail = p;
			n = 1;
		}
		else{
			tail->next = p;
			tail = p;
			n++;
		}

		// return the success information
		return 1;
	}
	// handle the exception
	catch(AllocFail &e){
		// print out the exception information
		cout << "Error: " << e.what() << endl;
		// return the failed information
		return 0;
	}
}

// the dequeue function
template <class Type>
bool Queue<Type>::outQueue(Type &data){
	ListItem<Type> *p;

	try{
		// if the queue is empty, throw an exception class
		if(!n)
			throw OutEmpty();

		// record the data of the first in the queue
		data = head->d;
		// delete the first node of the queue
		if(n == 1){
			delete head;
			head = tail = NULL;
		}
		else{
			p = head->next;
			delete head;
			head = p;
		}
		n--;

		// return the success infotmation
		return 1;
	}
	// handle the exception
	catch(OutEmpty &e){
		// print out the exception information
		cout << "Error: " << e.what() << endl;
		// return the failed information
		return 0;
	}
}

// the data printer function
template <class Type>
void Queue<Type>::printOut(){
	ListItem<Type> *p;

	if(!n){
		// if the queue is empty
		cout << "Empty queue." << endl;
		return;
	}
	// print each data in the queue out
	p = head;
	for(int i = 0; i < n; i++){
		cout << "No." << i << " : " << p->d << endl;
		p = p->next;
	}
}