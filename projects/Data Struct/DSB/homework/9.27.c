#include<stdio.h>
#define maxn 100
#define Adj 1		//adjacency
#define Dis 0		//disjunct

typedef int Matrix[maxn+2][maxn+2];

void DFS(Matrix,int,int,int);
void PostView(Matrix,int,int,int,int *,int []);

int main(void){
	int n,m,x,y,i,k;

	static Matrix a,r;
	static int o[maxn+1],f[maxn+1];

	scanf("%d%d",&n,&m);
	for(i=0;i<m;i++){
		scanf("%d%d",&x,&y);
		a[x][y]=r[y][x]=Adj;
	}

	k=0;
	for(i=1;i<=n;i++)
		if(!f[i])PostView(a,n,i,o,&k,f);

	while(k){
		while(!f[o[k]])k--;
		DFS(r,n,o[k],f);
		printf("\n");
		k--;
	}
}

void DFS(Matrix r,int n,int k,int f[]){
	int i;

	printf("%d ",k);
	f[k]=0;
	for(i=1;i<=n;i++)
		if(r[k][i]&&f[i])DFS(r,n,i,f);
}

void PostView(Matrix a,int n,int p,int o[],int *k,int f[]){
	int i;

	f[p]=1;
	for(i=1;i<=n;i++)
		if(a[p][i]&&!f[i])PostView(a,n,i,o,k,f);
	o[++(*k)]=p;
}