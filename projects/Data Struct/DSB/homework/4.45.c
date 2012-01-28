#include<stdio.h>
typedef struct BiThrNode{
	int d;
	struct BiThrNode *Left,*Right;
	int LTag,RTag;
}BiThrNode,*BiThrTree;

BiThrTree pre;

void InThread(BiThrTree p){
	if(p){
		InThread(p->Left);
		if(!p->Left){
			p->Left=pre;
			p->LTag=1;
		}
		if(!pre->Right){
			pre->Right=p;
			pre->RTag=1;
		}
		pre=p;
		InThread(p->Right);
	}
}

void Insert(int d,BiThrTree p){

}

void InTraver(BiThrTree Thr){
	BiThrTree p;
	p=Thr->Left;
	while(p!=Thr){
		while(!p->LTag)	p=p->Left;
		printf("%d\t",p->d);
		while(p->RTag&&p->Right!=Thr){
			p=p->Right;
			printf("%d\t",p->d);
		}
		p=p->Right;
	}
}

int main(void){
	BiThrTree Thr,t;
	int d;

	Thr->Right=Thr;
	Thr->RTag=0;
	if(t){
		Thr->Left=t;
		Thr->LTag=0;
		pre=Thr;
		InThread(t);
		pre->Right=Thr;
		pre->RTag=1;
	}
	else{
		Thr->Left=Thr;
		Thr->LTag=1;
	}
}
