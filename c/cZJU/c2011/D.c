#include <stdio.h>

void sort(double *a, int *b, int n) {
	int i, j;
	double tmp;
	int tb;

	for(i = 0; i < n - 1; i++) {
		for(j = i; j < n; j++) {
			if(a[i] > a[j]) {
				tmp = a[i];
				a[i] = a[j];
				a[j] = tmp;

				tb = b[i];
				b[i] = b[j];
				b[j] = tb;
			}
		}
	}
}

double Change(char *str) {
	double ans;
	int a, b, c, d, e, f;

	ans = 0;
	sscanf(str, "%d-%d-%d %d:%d", &a, &b, &c, &d, &e);
	ans = a;
	ans = ans * 100 + b;
	ans = (ans * 100) + c;
	ans = (ans * 100) + d;
	ans = (ans * 100) + e;

	return ans;
}

int main(void) {
	int T, n, m, i, j, c;
	double a[100];
	char str[100][100];
	int b[100];

	scanf("%d", &T);
	gets(str[0]);
	while(T--) {
		scanf("%d", &n);
		gets(str[0]);
		for(i = 0; i < n; i++) {
			gets(str[i]);
			a[i] = Change(str[i]);
			b[i] = i;
		}
		sort(a, b, n);

		for(i = 0; i < n; i++)
			puts(str[b[i]]);
	}

	return 0;
}
