#include<stdio.h>
int main(){
	long int n,i,k,t;

	scanf("%ld",&t);
	for(i=0;i<t;i++){
		scanf("%ld%ld",&n,&k);
		if((n-1)%(k+1))printf("Yes\n");
		else printf("No\n");
	}
}