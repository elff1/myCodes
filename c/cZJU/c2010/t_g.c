#include<stdio.h>
#include<string.h>

typedef char *string[100];
typedef string list[500];

void insert(string name,list staff,int n){
	int i;
	if(!n){
		strcpy(staff[n],name);
		return;
	}
	n--;
	for(i=n;i>=0;i--)
		if(strcmp(staff[i],name)>0)
			strcpy(staff[i+1],staff[i]);
		else
			break;
	strcpy(staff[i+1],name);
}

int find(string name,list staff,int n){
	int i;

	for(i=0;i<n;i++)
		if(strcmp(staff[i],name)==0)
			return i;
	return -1;
}

int main(){
	int t,n,m,i,j,k,s;
	string name;
	list staff,all;
	int ans[100];

	scanf("%d",&t);
	for(i=0;i<t;i++){
		s=0;

		scanf("%d",&n);
		getchar();
		for(j=0;j<n;j++)
			gets(all[j]);

		scanf("%d",&m);
		getchar();
		for(j=0;j<m;j++){
			gets(name);
			insert(name,staff,j);
		}

		for(j=0;j<m;j++)
			if(k=find(staff[j],all,n),k!=-1)
				ans[s++]=j;

		printf("%d\n",s);
		if(s)
			for(j=0;j<s;j++){
				/*printf("%d\n",ans[j]);*/
				puts(staff[ans[j]]);
			}
		else
			puts("None!");
		if(i!=t-1)
			printf("\n");
	}
}