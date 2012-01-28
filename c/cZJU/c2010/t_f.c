#include<stdio.h>

int main(){
	long int t,n,w,x,y,i,j,s;

	scanf("%ld",&t);
	for(i=0;i<t;i++){
		s=0;
		scanf("%ld%ld",&n,&y);
		for(j=0;j<n;j++){
			scanf("%ld",&x);
		}
		for(j=0;j<n;j++){
			scanf("%ld",&x);
			s+=x;
		}
		printf("%d\n",s);
	}
}