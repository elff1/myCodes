#include <stdio.h>/*This is a min heap.*/
#define maxn 1000

typedef struct HeapStruct{
	int n,* d[maxn];
}HeapStruct,*Heap;

void swap(int *x,int *y){
}

void Down(Heap h){
	int i,r,l;
	for(i=1;i<<1+1<=h->n;){
		l=i<<1;
		r=l+1;
		if(r<=h->n)
			if(h->d[i]<h->d[l]||h->d[i]<h->d[r])
				if(h->d[l]<h->d[r]){
					swap(h->d[i],h->d[l]);
					i=l;
				}
				else{
					swap(h->d[i],h->d[r]);
					i=r;
				}
			else break;
		else
			if(h->d[i]<h->d[l]){
				swap(h->d[i],h->d[l]);
				i=l;
			}
			else break;
	}
}

void Up(Heap h){
	int i,p;
	for(i=h->n;i>>1>0;){
		p=i>>1;
		if(h->d[i]<h->d[p]){
			swap(h->d[i],h->d[p]);
			i=p;
		}
		else break;
	}
}

int main(void){
	Heap h;
	int x;

	Down(h);
	Up(h);
}
