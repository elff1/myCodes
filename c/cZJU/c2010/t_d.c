#include<stdio.h>
#include<string.h>

typedef char *string;

int main(){
	int t,n,m,num,i,j;
	string a[21][21];
	char tmp[5001];
	char c;

	scanf("%d",&t);
	for(i=0;i<t;i++){
		scanf("%d%d",&n,&m);

		num=0;
		tmp="";
		while((c=getchar())!='\n'){
			if(c!='#'){
				k=0;
				tmp[k]=c;
				while((c=getchar())!='#')
					tmp[++k]=c;
				tmp[++k]='\0';
				a[