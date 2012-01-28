// ListItem.h: interface for the ListItem class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _ListItem_H
#define _ListItem_H

// the pre-defination of Queue for ListItem class.
template <class Type> class Queue;

template <class Type>
class ListItem{
	// Queue class is the friend class of ListItem.
	friend class Queue<Type>;

	// the constructor
	ListItem(const Type &data): d(data), next(0){}
	// the destructor
	~ListItem(){}

	// the data
	Type d;
	// the pointer of the next data
	ListItem<Type> *next;
};

#endif // _ListItem_H
