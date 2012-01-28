#include <stdio.h>
#include <math.h>

int main(){
	double x;

	while(scanf("%lf",x),x!=0)
		printf("%.2f",round(x));
}