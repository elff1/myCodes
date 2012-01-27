#include <stdio.h>

int main(void) {
	int n;
	int t;
	int i;
	int a[110];

	scanf("%d", &n);
	for(i = 1; i <= n; i++) {
		scanf("%d", &t);
		a[t] = i;
	}

	for(i = 1; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("%d\n", a[n]);

	return 0;
}
