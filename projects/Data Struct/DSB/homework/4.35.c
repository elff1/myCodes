#include<stdio.h>
#define maxn 1000

typedef struct Node *Tree;

Tree Insert(int,Tree);
void LevelOut(Tree);
void Print(Tree);

struct Node{
	int d;
	Tree left,right;
};

int main(void){
	Tree t;
	int d,n,i;

	printf("n:");							/*Get the n integers*/
	scanf("%d",&n);
	printf("Input the n integers:\n");
	t=NULL;
	for(i=0;i<n;i++){
		scanf("%d",&d);
		t=Insert(d,t);						/*Creat the binary search tree*/
	}
	Print(t);
	printf("\n");
	LevelOut(t);							/*List out the nodes in level-order*/
}

Tree Insert(int d,Tree t){
	if(t==NULL){
		t=malloc(sizeof(struct Node));
		if(t==NULL)
			printf("Out of space!!!");
		else{
			t->d=d;
			t->left=t->right=NULL;
		}
	}
	else
		if(d<t->d)
			t->left=Insert(d,t->left);
		else
			if(d>t->d)
				t->right=Insert(d,t->right);
	return t;
}

void LevelOut(Tree t){
	Tree l[maxn];
	int front,rear;

	front=rear=0;
	l[0]=t;
	while(front<=rear){
		t=l[front++];
		if(t->left)
			l[++rear]=t->left;
		if(t->right)
			l[++rear]=t->right;
		printf("%d\t",t->d);
	}
	printf("\n");
}

void Print(Tree t){
	if(t->left)
		Print(t->left);
	printf("%d\t",t->d);
	if(t->right)
		Print(t->right);
}