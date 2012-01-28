/* Author: Zhao Bingqian; ID: 3090103420; No.01 */
#include<stdio.h>
#define maxn 20
#define maxm 10
#define mank 1000

typedef struct{
	int n,t;
}Line;

typedef struct HeapStruct *Heap;
struct HeapStruct{
	int n;
	int k[maxn*maxm+1];
};

typedef struct{
	int l,t,d;
}Wait;

void InLine(int,int,Line[],Heap);
void InHeap(int,Heap);
int OutHeap(Heap);
int compare(int,int);
void Output(int);

Wait w[mank+1];
int n,m,c;

int main(void){
	int x,i,k,q;
	Line l[maxn+1];
	Heap h;

	h=NULL;
	h=malloc(sizeof(struct HeapStruct));
	if(!h){
		printf("Out of space!");
		exit(1);
	}

	scanf("%d",&n);
	w[0].t=0;
	while(n>0){
		scanf("%d%d%d",&m,&k,&q);
		c=n*m;
		for(i=1;i<=n;i++)
			l[i].n=l[i].t=0;
		l[0].n=maxm+1;
		h->n=h->k[0]=0;
		for(i=1;i<=k;i++){
			scanf("%d",&x);
			InLine(x,i,l,h);
			w[i].d=x;
		}
		for(i=1;i<=q;i++){
			scanf("%d",&x);
			/*printf("%d %d\n",w[x].t,w[x].d);*/
			Output(x);
		}
		scanf("%d",&n);
	}
	free(h);
}

void InLine(int x,int k,Line l[],Heap h){
	int i,lk;

	if(h->n<c)
		if(n!=1)
			for(lk=1,i=2;i<=n;i++){
				if(l[i].n<l[lk].n)lk=i;
			}
		else lk=1;
	else{
		lk=w[OutHeap(h)].l;
		l[lk].n--;
	}
	l[lk].t+=x;
	l[lk].n++;
	w[k].l=lk;
	w[k].t=l[lk].t;
	InHeap(k,h);
}

void InHeap(int k,Heap h){
	int i;
	
	if(h->n>maxn*maxm+1){
		printf("Heap is full");
		exit(1);
	}
	for(i=++h->n;compare(h->k[i/2],k);i/=2)
		h->k[i]=h->k[i/2];
	h->k[i]=k;
}

int OutHeap(Heap h){
	int i,child;
	int min,last;

	if(h->n<1){
		printf("Heap is empty");
		exit(1);
	}
	min=h->k[1];
	last=h->k[h->n--];
	for(i=1;i*2<=h->n;i=child){
		child=i*2;
		if(child!=h->n&&compare(h->k[child],h->k[child+1]))
			child++;
		if(compare(last,h->k[child]))
			h->k[i]=h->k[child];
		else
			break;
	}
	h->k[i]=last;
	return min;
}

int compare(int a,int b){
	return w[a].t>w[b].t||w[a].t==w[b].t&&w[a].l>w[b].l;
}

void Output(int k){
	int hour,minute;

	if(w[k].t-w[k].d>=540)printf("Sorry\n");
	else{
		hour=w[k].t/60+8;
		minute=w[k].t%60;
		if(hour<10)printf("0");
		printf("%d:",hour);
		if(minute<10)printf("0");
		printf("%d\n",minute);
	}
}