/*
* cy_G12_P3.c - the program for Project 3 of Fundamentals of Data Structures.
* Copyright (C) Zhao Bingqian of Group 12. All rights reserved.
* Purpose: reconstruct the input sequence from the given status of the hash table.
* Instructor: Chenyue.
* Version: 2010/10/26
*/

#include<stdio.h>

/*
*member 'position' is used to store the original position of this element in the hash table
*define the max data number.
*/
#define maxn 1000

/*
*define the struct of link list which is used in adjacency list struct and queue struct.
*member 'd' is used to store the data of the node.
*member 'next' is used to point the next node.
*/
typedef struct Node *List;
struct Node{
	int d;
	List next;
};

/*
*define the n-sized array to store the input data and the in-degree of each vertex.
*/
typedef int Data[maxn];

/*
*define the adjacency list to store the topological order of each input data.
*/
typedef List AdjList[maxn];

void work(int);
void insert(List,int,Data);
List NewNode(void);
void ErrOut(char *);

int main(void){
	int n;
	/*handle each n-sized data by calling function work(), until n equals 0.*/
	for(scanf("%d",&n);n;scanf("%d",&n)) work(n);
}

/*handle the case which has n input data.*/
void work(int n){
	/*
	*variable 'Num' is the number of the nonnegative data.
	*variable 'x' is the remainder of a data mod n.
	*/
	int Num,i,j,k,x;
	/*
	*array 'd' is used to store the input data.
	*array 'r' is used to store the in-degree of each vertex.
	*/
	Data d,r;
	/*adjacency list m is used to store the topological relation of each input data.*/
	AdjList m;
	/*queue 'h' is used to store the vertexs with 0 in-degree.*/
	List h,p;

	/*
	*read in the n data, count the nonnegative data number, creat an empty adjacency list.
	*/
	Num=0;
	for(i=0;i<n;i++){
		scanf("%d",&d[i]);
		if(d[i]>=0)Num++;
		r[i]=0;
		m[i]=NewNode();
		m[i]->next=NULL;
	}

	/*
	*build up the adjacency list according to the input order
	*initialize the queue which stores the vertexs with 0 in-degree.
	*/
	h=NewNode();
	h->next=NULL;

	for(i=0;i<n;i++)
		if(d[i]>=0){
			/*count the collisions of data[i] which equals to its in-degree r[i].*/
			x=d[i]%n;
			r[i]=i-x;
			if(r[i]<0)r[i]+=n;
			/*if there are collisions of data[i], add them into the adjacency list.*/
			if(r[i])
				for(j=x;j!=i;){
					/*for each collision, add into the adjacency list.*/
					p=NewNode();
					p->d=i;
					p->next=m[j]->next;
					m[j]->next=p;
					/*count the next collision.*/
					j++;
					if(j==n)j=0;
				}
			/*if there is no collision of data[i], add it into the queue.*/
			else
				insert(h,i,d);
		}

	/*
	*topological sort the data according the adjacency list using the queue.
	*/
	while(h->next){
		/*dequeue the first item, copy the data, free the space.*/
		p=h->next;
		h->next=p->next;
		k=p->d;
		free(p);

		/*
		*print out the input sequence separated by a space, 
		*and no extra space at the end of the line.
		*/
		Num--;
		if(Num)
			printf("%d ",d[k]);
		else
			printf("%d\n",d[k]);

		/*
		*decrease the in-degree of adjacency nodes, 
		*add the new 0-in-degree node into the queue.
		*/
		for(p=m[k]->next;p;p=p->next)
			if(--r[p->d]==0)insert(h,p->d,d);
	}
}

/*
*insert the new item into the queue in increasing order according to its data.
*/
void insert(List h,int i,Data d){
	int key;
	List p,q;

	/*create a new node 'p' to store the item.*/
	p=NewNode();
	p->d=i;
	key=d[i];

	/*search for right position in the queue of the item to insert in from the head.*/
	for(q=h;q->next&&d[q->next->d]<key;q=q->next);
	p->next=q->next;
	q->next=p;
}

/*apply for a new link list node.*/
List NewNode(void){
	List p;	
	p=NULL;
	p=malloc(sizeof(struct Node));
	if(!p)ErrOut("Out of space!");
	return p;
}

/*print out the error information and quit.*/
void ErrOut(char *str){
	puts(str);
	exit(1);
}