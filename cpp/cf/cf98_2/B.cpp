#include <stdio.h>

int main(void) {
	int n, d;
	int a[5005];
	int i, ans;

	for(i = 1; i <= 5000; i++)
		a[i] = 0;
	scanf("%d", &n);
	for(i = 0; i < n; i++) {
		scanf("%d", &d);
		a[d]++;
	}
	ans = 0;
	for(i = 1; i <= n; i++)
		if(a[i])
			ans += a[i] - 1;
	for(i = n + 1; i <= 5000; i++)
		ans += a[i];
	printf("%d\n", ans);
	return 0;
}
