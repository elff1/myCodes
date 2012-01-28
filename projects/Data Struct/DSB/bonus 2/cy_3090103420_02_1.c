/* Author: Zhao Bingqian; ID: 3090103420; No.02 */
#include<stdio.h>

#define maxn 500
#define maxq 1000

typedef struct Node *List;
struct Node{
	int x,y;
	List next;
};

void work(int m,int n);
int infect(List q,int t);
List NewNode();
void FreeList(List);

int a[maxn+2][maxn+2];
int d,mn;
List e[maxq+1],h[maxq+1];

int ix[4]={-1,0,1,0};
int iy[4]={0,1,0,-1};

int main(void){
	int n,m,cases;

	cases=0;
	while(scanf("%d%d",&m,&n),m){
		if(cases)printf("\n");
		cases++;
		printf("Scenario #%d\n",cases);
		work(m,n);
	}
}

void work(int m,int n){
	int Q,T,i,j,k,x;
	List p,q;

	mn=m*n;
	T=0;
	for(i=1;i<=m;i++){
		for(j=1;j<=n;j++){
			scanf("%d",&x);
			a[i][j]=x;
			if(x>=0){
				T++;
				mn--;
				h[x]=NewNode();
				h[x]->x=1;
				p=NewNode();
				p->x=i;p->y=j;
				p->next=NULL;
				h[x]->next=p;
				e[x]=p;
			}
		}
		a[i][0]=a[i][n+1]=maxq+1;
	}
	for(j=1;j<=n;j++)
		a[0][j]=a[m+1][j]=maxq+1;

	d=0;
	while(mn){
		d++;
		for(i=1;i<=T;i++){
			p=h[i];
			while(q=p->next)
				if(!infect(q,i)){
					p->next=q->next;
					free(q);
				}
				else p=q;
		}
	}

	scanf("%d",&Q);
	for(i=1;i<=Q;i++){
		scanf("%d",&x);
		printf("%d\n",h[x]->x);
	}
	for(i=1;i<=T;i++)
		FreeList(h[i]);
}

int infect(List q,int t){
	int i,nx,ny,x,y,f;
	List np;

	f=4;
	x=q->x;y=q->y;
	for(i=0;i<4;i++){
		nx=x+ix[i];
		ny=y+iy[i];
		if(a[nx][ny]>=0)
			f--;
		else if((-a[nx][ny])<=d){
			mn--;
			a[nx][ny]=t;
			np=NewNode();
			np->next=NULL;
			np->x=nx;np->y=ny;
			(h[t]->x)++;
			e[t]->next=np;
			e[t]=np;
		}
	}
	return f;
}

List NewNode(){
	List p;

	p=NULL;
	p=malloc(sizeof(struct Node));
	if(!p){
		printf("Out of space!");
		exit(1);
	}
	return p;
}

void FreeList(List p){
	List q;

	while(p){
		q=p->next;
		free(p);
		p=q;
	}
}