#ifndef _LinkStack_H
#define _LinkStack_H

#include"LinkList.h"

class LinkStack : public LinkList{					// the stack using link list
public :
	LinkStack(){}									// the constructor
	~LinkStack(){}									// the destructor
	const bool IsEmpty(){return (n == 0);}			// judge whether the stack is empty
	const int &Top(){return head->next->data;}		// get the top element in the stack
	void Push(const int d){insert(0,d);}			// push a new element into the stack
	void Pop(){del(0);}								// delete the top element in the stack
	void MakeEmpty(){								// make the stack empty
		while(n)
			del(0);
	}
};

#endif //_LinkStack_H