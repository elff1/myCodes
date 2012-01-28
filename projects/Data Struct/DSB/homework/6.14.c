#include<stdio.h>
#define maxn 1000

void irMergesort(int d[],int n);
void Merge(int d[],int tmpd[],int p,int q,int re);

int main(void){
	int d[maxn];
	int n,i;

	scanf("%d",&n);
	for(i=0;i<n;i++)scanf("%d",&d[i]);
	irMergesort(d,n);
	for(i=0;i<n;i++)printf("%d\t",d[i]);
	printf("\n");
}

void irMergesort(int d[],int n){
	int *tmpd;
	int p,q,inc,inc2;

	tmpd=NULL;
	tmpd=malloc(n*sizeof(int));
	if(!tmpd){
		printf("Out of space!");
		exit(1);
	}
	for(inc=1;inc<n;inc=inc2){
		inc2=inc+inc;
		for(p=0,q=inc2-1;q<n;p+=inc2,q+=inc2)
			Merge(d,tmpd,p,p+inc,q);
		if(p+inc<n)
			Merge(d,tmpd,p,p+inc,n-1);
	}
}

void Merge(int d[],int tmpd[],int p,int q,int re){
	int le,i,s;

	i=s=p;
	le=q-1;
	while(p<=le&&q<=re)
		if(d[p]<d[q])tmpd[i++]=d[p++];
		else tmpd[i++]=d[q++];
	while(p<=le)tmpd[i++]=d[p++];
	while(q<=re)tmpd[i++]=d[q++];
	for(i=s;i<=re;i++)d[i]=tmpd[i];
}