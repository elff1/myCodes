#include<stdio.h>

typedef struct Node *lptr;
struct Node{
	int c,k;
	lptr n;
};

lptr new(){
	lptr p;
	p=NULL;
	p=(lptr)malloc(sizeof(struct Node));
	if(p==NULL){
		printf("Out of space!");
		exit(1);
	}
	return p;
}

lptr addition(lptr p,lptr q){
	lptr a,b,r;

	r=new();
	r->n=NULL;
	a=r;

	p=p->n;q=q->n;
	while(p!=NULL||q!=NULL)
		if(p!=NULL&&q==NULL||p->k>q->k){
			b=new();
			*b=*p;
			b->n=NULL;
			a->n=b;
			a=a->n;
			p=p->n;
		}
		else if(q!=NULL&&p==NULL||p->k<q->k){
			b=new();
			*b=*q;
			b->n=NULL;
			a->n=b;
			a=a->n;
			q=q->n;
		}
		else{
			if(p->c+q->c!=0){
				b=new();
				b->k=p->k;
				b->c=p->c+q->c;
				b->n=NULL;
				a->n=b;
				a=a->n;
			}
			p=p->n;
			q=q->n;
		}
	return r;
}

int main(void){
	lptr p,q,r;
	p=q=NULL;
	r=addition(p,q);
}