/* Author: Zhao Bingqian; ID: 3090103420; No.02 */
#include<stdio.h>

#define maxn 500
#define maxq 1000

typedef struct Node *List;
struct Node{
	int x,y;
	List next;
};

void initialization(void);
void work(int m,int n);
void infect(List q,int t);
List NewNode();
void FreeList(List);
void PrintList(List p);

int a[maxn+2][maxn+2];
int d,mn;
List e[maxq+1],h[maxq+1],di[maxq+1];

int ix[4]={-1,0,1,0};
int iy[4]={0,1,0,-1};

int main(void){
	int n,m,cases;

	initialization();
	cases=0;
	while(scanf("%d%d",&m,&n)!=EOF){
		/*if(cases)printf("\n");
		cases++;
		printf("Scenario #%d\n",cases);*/
		work(m,n);
	}
}

void work(int m,int n){
	int Q,T,i,j,k,x,type;
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
		p=di[d]->next;
		while(p){
			q=p->next;
			mn--;
			type=a[p->x][p->y];
			p->next=NULL;
			e[type]->next=p;
			e[type]=p;
			p=q;
		}
		di[d]->next=p;
		for(i=1;i<=T;i++){
			p=h[i];
			while(q=p->next){
					infect(q,i);
					p->next=q->next;
					free(q);
				}
		}

		for(i=1;i<=maxq;i++) if(di[i]->next){
			printf("Day %d:",i);
			PrintList(di[i]->next);
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

void infect(List q,int t){
	int i,nx,ny,x,y,level;
	List np;

	x=q->x;y=q->y;
	printf("No.%d:%d %d\n",mn,x,y);
	for(i=0;i<4;i++){
		nx=x+ix[i];
		ny=y+iy[i];
				level=-a[nx][ny];
		if(level>0){
				np=NewNode();
				np->next=NULL;
				np->x=nx;np->y=ny;
				(h[t]->x)++;
				a[nx][ny]=t;
			if(level<=d){
				mn--;
				e[t]->next=np;
				e[t]=np;
			}
			else{
				np->next=di[level]->next;
				di[level]->next=np;
			}
		}
	}
}

void initialization(void){
	int i;
	for(i=1;i<=maxq;i++){
		di[i]=NewNode();
		di[i]->next=NULL;
	}
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

void PrintList(List p){
	for(;p;p=p->next)
		printf("%d %d(%d),",p->x,p->y,a[p->x][p->y]);
	printf("\n");
}