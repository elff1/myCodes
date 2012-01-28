#include<iostream>
#include"LinkList.h"

using namespace std;

// the constructor
LinkList ::LinkList(){
	head = new LinkNode;
	head->next = NULL;
	tail = head;
}

// the destructor
LinkList ::~LinkList(){
	Link p, q;

	p = head;
	while(p){									// free all the space of the list
		q = p->next;
		delete p;
		p = q;
	}
}

// get the element at the position k
const int& LinkList::operator [](const int k) const{
	if(k == n - 1)
		return tail->data;
	else if(k < n){
		Link p = head->next;
		for(int i = 0; i < k; i++)				// find the position k
			p = p->next;
		return p->data;
	}
}

// attach the value at end
void LinkList::attach(const int d){
	Link p = new LinkNode;						// new a link list node
	p->data = d;
	p->next = tail->next;
	tail->next = p;								// attach it to the end of the list
	tail = p;
	n++;										// increase the number counter
}

// insert the value before the position k
void LinkList::insert(const int k, const int d){
	Link p = head;
	for(int i = 0; i < k; i++)					// find the place to be inserted
		p = p->next;

	Link q = new LinkNode;						// new a link list node
	q->data = d;
	q->next = p->next;							// insert it to the list
	p->next = q;
	n++;										// increase the number counter
}

// delete the value at position k
void LinkList::del(const int k){
	Link p = head;
	for(int i = 0; i < k; i++)					// find the position k
		p = p->next;

	Link q = p->next;
	p->next = q->next;							// delete the node
	delete q;
	n--;										// decrease the number counter
}

// print out all the information in the list
void LinkList::prtAll(){
	cout << "N: " << n << endl;
	Link p = head->next;
	while(p){
		cout << p->data << '\t';
		p = p->next;
	}
	cout << endl;
}