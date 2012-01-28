#include<stdio.h>

typedef struct Node *Stack;

void push(int,Stack);
int top(Stack);
void pop(Stack);
int IsEmpty(Stack);
void error();

struct Node{
	int d;
	Stack Next;
};

int main(void){
	char c;
	int d,x,y;
	Stack s;
	
	s=NULL;								/*Creat an empty stack*/
	s=malloc(sizeof(struct Node));
	if(s==NULL){
		printf("Out of space!");
		exit(1);
	}
	s->Next=NULL;
	printf("Input the postfix expression end with "=":\n");
	c=getchar();							/*Get the expression and handle online*/
	while(c!='='){
		while(c==' '||c=='\n') c = getchar();
		if(c>='0'&&c<='9'){					/*Separate the integers and push into the stack*/
			d=c-'0';
			c=getchar();
			while(c>='0'&&c<='9'){
				d=d*10+c-'0';
				c=getchar();
			}
			push(d,s);
		}
		else if(c=='+'||c=='-'||c=='*'||c=='/'){		/*Handle the operator*/
			if(IsEmpty(s))error();
			else{
				y=top(s);
				pop(s);
			}
			if(IsEmpty(s))error();
			else{
				x=top(s);
				pop(s);
			}
			if(c=='/'&&y==0)error();
			switch(c){
				case '+':d=x+y;break;
				case '-':d=x-y;break;
				case '*':d=x*y;break;
				case '/':d=x/y;break;
			}
			push(d,s);
			c=getchar();
		}
		else if(c=='=')break;
		else error();
	}
	if(IsEmpty(s))error();						/*Output the answer*/
	else{
		d=top(s);
		pop(s);
	}
	if(!IsEmpty(s))error;
	printf("%d\n",d);
}

void push(int d,Stack s){						/*Push a new item into the stack*/
	Stack p;

	p=NULL;
	p=malloc(sizeof(struct Node));
	if(p==NULL){
		printf("Out of space!");
		exit(1);
	}
	p->d=d;
	p->Next=s->Next;
	s->Next=p;
}

int top(Stack s){							/*Return the top item*/
	return(s->Next->d);
}

void pop(Stack s){							/*Delete the top item*/
	Stack p;

	p=s->Next;
	s->Next=p->Next;
	free(p);
}

int IsEmpty(Stack s){							/*Judge the stack is empty or not*/
	return(s->Next==NULL);
}

void error(){								/*Print the error information and shut down*/
	printf("Input error!");
	exit(1);
}
