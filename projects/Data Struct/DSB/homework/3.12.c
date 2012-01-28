#include<stdio.h>

typedef struct Node *lptr;
struct Node{
	int d;
	lptr Next;
};

lptr reverse(lptr p){
	lptr q,r;
	if(p->Next==NULL)return p;
	q=p->Next;
	p->Next=NULL;
	r=q->Next;
	while(r!=NULL){
		q->Next=p;
		p=q;
		q=r;
		r=r->Next;
	}
	q->Next=p;
	return q;
}

int main(void){
	lptr p;
	p=NULL;
	p=reverse(p);
}