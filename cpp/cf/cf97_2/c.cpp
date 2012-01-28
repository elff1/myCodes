#include <stdio.h>
#include <cstdlib>
#include <time.h>
#define MaxN (100000)

void qsort(int *a, int p, int q) {
	int m, i, j, tmp;

	i = p;
	j = q;
	m = a[rand() % (q - p + 1) + p];
	do {
		while(a[i] < m)
			i++;
		while(a[j] > m)
			j--;
		if(i <= j){
			tmp = a[i];
			a[i] = a[j];
			a[j] = tmp;
			i++;
			j--;
		}
	} while(i <= j);
	if(p < j)
		qsort(a, p, j);
	if(i < q)
		qsort(a, i, q);
}

int main(void) {
	int a[MaxN];
	int i, j;
	int n;

	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d", &a[i]);

	srand(time(0));
	qsort(a, 0, n - 1);

	if(a[n - 1] == 1) {
		for(i = 1; i < n; i++)
			printf("%d ", a[i]);
		printf("2\n");
	}
	else {
		printf("1");
		for(i = 0; i < n - 1; i++)
			printf(" %d", a[i]);
		printf("\n");
	}

	return 0;
}
