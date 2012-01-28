#include <stdio.h>

int Include(int a[][2], int p, int q) {
	if(a[p][0] > a[q][0] && a[p][1] < a[q][1])
		return 1;
	return 0;
}

int main(void) {
	int a[100000][2];
	int n, i, j;
	int flag;
	int ans;

	scanf("%d", &n);
	for(i = 0; i < n; i++)
		scanf("%d%d", &a[i][0], &a[i][1]);
	ans = 0;
	for(i = 0; i < n; i++) {
		for(j = 0; j < n; j++)
			if(Include(a, i, j)) {
				ans++;
				break;
			}
	}
	printf("%d\n", ans);

	return 0;
}
