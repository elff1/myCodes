#include <stdio.h>
#define maxn 10000

void merge(int,int,int,int);
int find(int,int);

int main(void){
	int n,i,j,x,y,kinds;
	int p[maxn+1];
	char c;

	for(scanf("%d",&n);n!=EOF;scanf("%d",&n)){
		kinds=n;
		for(i=1;i<=n;i++)p[i]=-1;
		getchar();	
		while((c=getchar())!='S'){
			scanf("%d%d",&x,&y);
			getchar();
			if(c=='I')merge(p,x,y,&kinds);
			if(c=='C')(find(p,x)==find(p,y)) ? printf("yes"):printf("no");
		}
		if(kinds==1)
			printf("The network is connected.");
		else
			printf("There are %d components.",kinds);
		for(i=1;i<=n;i++)printf("%d\t",p[i]);printf("\n");
	}
}

void merge(int p[],int x,int y,int *kinds){
	int px,py;
	px=find(p,x);
	py=find(p,y);
	if(px==py)return;
	if(p[px]<p[py]){
		p[px]+=p[py];
		p[py]=px;
	}
	else{
		p[py]+=p[px];
		p[px]=py;
	}
	(*kinds)--;
}

int find(int p[],int x){
	int i,tmp,root;
	for(root=x;p[root]>0;root=p[root]);
	for(i=x;i!=root;i=tmp){
		tmp=p[i];
		p[i]=root;
	}
	return root;
}