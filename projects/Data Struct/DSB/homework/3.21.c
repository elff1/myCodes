#include <stdio.h>
#define maxn 1000

typedef struct StackRecord *Stack;

void push(int x,Stack s,int f);
int top(Stack s,int f);
void pop(Stack s,int f);
int IsEmpty(Stack s,int f);
int IsFull(Stack s,int f);
void error(char *str);

struct StackRecord{
	int h1,h2;
	int d[maxn];
};

int main(void){
	Stack s;
	int d;
	
	s=NULL;
	s=malloc(sizeof(struct StackRecord));
	if(s==NULL)
		error("Out of space");
	s->h1=0;
	s->h2=maxn-1;
	d=top(s,2);
	push(d,s,1);
	pop(s,2);
}

void push(int x,Stack s,int f){
	if(IsFull(s,f))
		error("Full Stack");
	else
		if(f==1)
			s->d[++s->h1]=x;
		else
			s->d[--s->h2]=x;
}

int top(Stack s,int f){
	if(IsEmpty(s,f))
		error("Empty Stack");
	else
		return(f==1?s->d[s->h1]:s->d[s->h2]);
}

void pop(Stack s,int f){
	if(IsEmpty(s,f))
		error("Empty Stack");
	else
		f==1?s->h1--:s->h2++;
}

int IsEmpty(Stack s,int f){
	return(f==1?s->h1==0:s->h2==maxn-1);
}

int IsFull(Stack s,int f){
	return(s->h1>s->h2);
}

void error(char *str){
	printf("%s\n",str);
}