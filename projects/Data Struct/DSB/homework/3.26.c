#include <stdio.h>
#define maxn 1000

typedef struct DequeRecord *Deque;

void Push(int,Deque);
void Inject(int,Deque);
int Pop(Deque);
int Eject(Deque);
int IsFull(Deque);
int IsEmpty(Deque);
void error(char);

struct DequeRecord{
	int front,rear;
	int d[maxn];
};

int main(void){
	Deque d;
	int x;

	d=NULL;
	d=malloc(sizeof(struct DequeRecord));
	if(d==NULL)
		error("Out of space");
	d->rear=maxn-1;
	d->front=0;

	Push(x,d);
	Inject(x,d);
	x=Pop(d);
	x=Eject(d);
}

void Push(int x,Deque d){
	if(IsFull(d))
		error("Deque full");
	else{
		d->front==0?d->front=maxn-1:d->front--;
		d->d[d->front]=x;
	}
}

void Inject(int x,Deque d){
	if(IsFull(d))
		error("Deque full");
	else{
		d->rear==maxn-1?d->rear=0:d->rear++;
		d->d[d->rear]=x;
	}
}

int Pop(Deque d){
	int x;
	if(IsEmpty(d))
		error("Deque empty");
	else{
		x=d->d[d->front];
		d->front==maxn-1?d->front=0:d->front++;
		return x;
	}
}

int Eject(Deque d){
	int x;
	if(IsEmpty(d))
		error("Deque empty");
	else{
		x=d->d[d->rear];
		d->rear==0?d->rear=maxn-1:d->rear--;
		return x;
	}
}

int IsFull(Deque d){
	return(d->front-d->rear==2||d->front-d->rear==2-maxn);
}

int IsEmpty(Deque d){
	return(d->front-d->rear==1||d->front-d->rear==1-maxn);
}

void error(char *str){
	printf("%s\n",str);
}